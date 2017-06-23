/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017
 * email:  daddinuz@gmail.com
 */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "http.h"

/*
 * Private types definitions
 */
typedef struct __buffer_t {
    size_t size;
    char *memory;
} __buffer_t;

/*
 * Private functions declarations
 */
static struct curl_slist *__make_headers(HttpDict *dict);
static void __die(const char *file, int line, const char *message);
static size_t __callback(void *content, size_t member_size, size_t members_count, void *user_data);

/*
 * API functions definitions
 */
const HttpResponse *http_request(HttpString method, HttpString url, HttpParams *params) {
    const HttpRequest *request = http_request_new(method, url, params->headers, params->body);
    int status_code = 0;
    HttpString effective_url = NULL;
    CURL *handler = curl_easy_init();
    struct curl_slist *headers_list = __make_headers(request->headers);
    __buffer_t headers_buffer = {0}, body_buffer = {0};

    if (NULL == handler) {
        __die(__FILE__, __LINE__, strerror(errno));
    }

    /* Set request options */
    curl_easy_setopt(handler, CURLOPT_URL, request->url);
    curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, request->method);
    curl_easy_setopt(handler, CURLOPT_HTTPHEADER, headers_list);
    curl_easy_setopt(handler, CURLOPT_HEADERFUNCTION, __callback);
    curl_easy_setopt(handler, CURLOPT_HEADERDATA, &headers_buffer);
    curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, __callback);
    curl_easy_setopt(handler, CURLOPT_WRITEDATA, &body_buffer);
    curl_easy_setopt(handler, CURLOPT_FOLLOWLOCATION, !params->no_follow_location);
    curl_easy_setopt(handler, CURLOPT_SSL_VERIFYPEER, !params->no_peer_verification);
    curl_easy_setopt(handler, CURLOPT_SSL_VERIFYHOST, !params->no_host_verification);
    if (request->body) {
        curl_easy_setopt(handler, CURLOPT_POSTFIELDS, request->body);
        curl_easy_setopt(handler, CURLOPT_POSTFIELDSIZE, strlen(request->body));
    }
    if (params->timeout > 0) {
        curl_easy_setopt(handler, CURLOPT_TIMEOUT, params->timeout);
    }

#ifndef NDEBUG
    /* Get verbose debug output */
    curl_easy_setopt(handler, CURLOPT_VERBOSE, 1L);
#endif

    /* Perform the request */
    CURLcode curl_errno = curl_easy_perform(handler);
    if (CURLE_OK != curl_errno) {
        __die(__FILE__, __LINE__, curl_easy_strerror(curl_errno));
    }

    /* Get the response info */
    curl_easy_getinfo(handler, CURLINFO_RESPONSE_CODE, &status_code);
    if (params->no_follow_location) {
        effective_url = http_string_copy(request->url);
    } else {
        char *tmp = NULL;
        curl_easy_getinfo(handler, CURLINFO_EFFECTIVE_URL, &tmp);
        effective_url = http_string_copy(tmp);
    }

    /* Terminate */
    curl_easy_cleanup(handler);
    curl_slist_free_all(headers_list);

    return http_response_new(
            request,
            status_code,
            effective_url,
            headers_buffer.memory,
            headers_buffer.size,
            body_buffer.memory,
            body_buffer.size
    );
}

/*
 * Private functions definitions
 */
bool __make_headers_callback(char *key, char *value, void *context) {
    struct curl_slist **headers_list_reference = context;
    const size_t BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, "%s: %s", key, value);
    *headers_list_reference = curl_slist_append(*headers_list_reference, buffer);
    return true;
}

struct curl_slist *__make_headers(HttpDict *dict) {
    if (NULL == dict) {
        return NULL;
    }
    struct curl_slist *headers_list = NULL;
    http_dict_each((HttpDict *) dict, __make_headers_callback, &headers_list);
    return headers_list;
}

void __die(const char *file, int line, const char *message) {
    fprintf(stderr, "\nAt: %s:%d\nError: %s\n", file, line, message);
    abort();
}

static size_t __callback(void *content, size_t member_size, size_t members_count, void *user_data) {
    __buffer_t *const buffer = user_data;
    const size_t real_size = member_size * members_count;

    buffer->memory = realloc(buffer->memory, buffer->size + real_size + 1);
    if (NULL == buffer->memory) {
        __die(__FILE__, __LINE__, strerror(errno));
        abort();
    }

    memcpy(&(buffer->memory[buffer->size]), content, real_size);
    buffer->size += real_size;
    buffer->memory[buffer->size] = 0;

    return real_size;
}
