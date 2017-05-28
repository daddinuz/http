/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017
 * email:  daddinuz@gmal.com
 */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "http.h"

#define BUFFER_SIZE     512

typedef struct HttpBuffer {
    size_t size;
    char *memory;
} HttpBuffer;

static void __die(const char *file, int line, const char *message);
static size_t __write_buffer_callback(void *contents, size_t size, size_t nmemb, void *userp);
static HttpResponse *__send_request(const char *file, int line, HttpRequest *request, bool allow_redirects, long timeout);

/*
 *
 */
HttpResponse *__http_perform(const char *file, int line, const HttpString method, HttpParams *params) {
    if (!(*params).url) {
        __die(file, line, "URL parameter is required");
    }
    HttpRequest *request = http_request_new(method, (*params).url, (*params).headers, (*params).body);
    return __send_request(file, line, request, (*params).allow_redirects, (*params).timeout);
}

/*
 *
 */
void __die(const char *file, int line, const char *message) {
    fprintf(stderr, "\nAt: %s:%d\nError: %s\n", file, line, message);
    abort();
}

static size_t __write_buffer_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    HttpBuffer *buffer = userp;

    buffer->memory = realloc(buffer->memory, buffer->size + realsize + 1);
    if(buffer->memory == NULL) {
        __die("", 0, strerror(errno));
        abort();
    }

    memcpy(&(buffer->memory[buffer->size]), contents, realsize);
    buffer->size += realsize;
    buffer->memory[buffer->size] = 0;

    return realsize;
}

HttpResponse *__send_request(const char *file, int line, HttpRequest *request, bool allow_redirects, long timeout) {
    int final_status_code = 0;
    const char *final_url = {0};
    char buffer[BUFFER_SIZE] = {0};
    CURL *handler = curl_easy_init();
    struct curl_slist *headers_list = NULL;
    HttpBuffer headers_buffer = {0}, body_buffer = {0};

    if (NULL == handler) {
        __die(file, line, strerror(errno));
    }

    /* setup raw_headers */
    if ((*request).headers) {
        HttpString header_key = (*request).headers[0].key, header_value = (*request).headers[0].value;
        for (size_t i = 0; header_key && header_value; i++, header_key = (*request).headers[i].key, header_value = (*request).headers[i].value) {
            snprintf(buffer, BUFFER_SIZE, "%s: %s", header_key, header_value);
            headers_list = curl_slist_append(headers_list, buffer);
        }
    }

    /* Set request options */
    curl_easy_setopt(handler, CURLOPT_URL, (*request).url);
    curl_easy_setopt(handler, CURLOPT_FOLLOWLOCATION, allow_redirects);
    curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, (*request).method);
    curl_easy_setopt(handler, CURLOPT_HTTPHEADER, headers_list);
    curl_easy_setopt(handler, CURLOPT_HEADERFUNCTION, __write_buffer_callback);
    curl_easy_setopt(handler, CURLOPT_HEADERDATA, &headers_buffer);
    curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, __write_buffer_callback);
    curl_easy_setopt(handler, CURLOPT_WRITEDATA, &body_buffer);
    if (timeout > 0) {
        curl_easy_setopt(handler, CURLOPT_TIMEOUT, timeout);
    }

#ifndef NDEBUG
    /* Get verbose debug output */
    curl_easy_setopt(handler, CURLOPT_VERBOSE, 1L);
#endif

    /* Perform the request */
    CURLcode curl_errno = curl_easy_perform(handler);
    if (CURLE_OK != curl_errno) {
        __die(file, line, curl_easy_strerror(curl_errno));
    }

    /* Get the response info */

    if (allow_redirects) {
        curl_easy_getinfo(handler, CURLINFO_EFFECTIVE_URL, &final_url);
    } else {
        final_url = (*request).url;
    }
    curl_easy_getinfo(handler, CURLINFO_RESPONSE_CODE, &final_status_code);

    /* Terminate */
    curl_easy_cleanup(handler);
    curl_slist_free_all(headers_list);

    return http_response_new(
            request,
            final_status_code,
            final_url,
            headers_buffer.memory,
            headers_buffer.size,
            body_buffer.memory,
            body_buffer.size
    );
}
