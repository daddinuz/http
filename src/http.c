/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmal.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <curl/curl.h>
#include "picohttpparser.h"
#include "strdup.h"
#include "http.h"
#include "__x_http_header__"


/************************************
 * Macro definitions
 */
#define _STR(s)         #s
#define STR(s)          _STR(s)
#define TRACE(msg)      "At: " __FILE__ ":" STR(__LINE__) "\r\n" msg

#define SX_BUFFER_SIZE  512
#define MD_BUFFER_SIZE  SX_BUFFER_SIZE * 2
#define LG_BUFFER_SIZE  MD_BUFFER_SIZE * 2

/************************************
 * Private functions declarations
 */
static void __request_initialize(CURL **handler, struct curl_slist **list, const char **url, HttpHeader *header);
static void __request_execute(CURL **handler, HttpResponse *response);
static void __request_terminate(CURL **handler, struct curl_slist **list);
static struct curl_slist *__make_header(HttpHeader *header);
static void __parse_header(HttpResponse *response);
static size_t __header_callback(void *data, size_t size, size_t nmemb, HttpResponse *response);
static size_t __response_callback(void *data, size_t size, size_t nmemb, HttpResponse *response);
static void __from_underscore_to_hyphen(char *dst, size_t max, const char *src);

/************************************
 * Public functions definitions
 */
HttpResponse http_delete(const char *url, const char *data, HttpHeader header) {
    CURL *handler = NULL;
    struct curl_slist *list = NULL;
    HttpResponse response = {.body_length=0, .raw_body=NULL, .header_length=0, .raw_header=NULL};

    __request_initialize(&handler, &list, &url, &header);
    curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(handler, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(handler, CURLOPT_POSTFIELDSIZE, strlen(data));
    __request_execute(&handler, &response);
    __request_terminate(&handler, &list);

    return response;
}

HttpResponse http_get(const char *url, HttpHeader header) {
    CURL *handler = NULL;
    struct curl_slist *list = NULL;
    HttpResponse response = {.body_length=0, .raw_body=NULL, .header_length=0, .raw_header=NULL};

    __request_initialize(&handler, &list, &url, &header);
    curl_easy_setopt(handler, CURLOPT_HTTPGET, 1);
    __request_execute(&handler, &response);
    __request_terminate(&handler, &list);

    return response;
}

HttpResponse http_head(const char *url, HttpHeader header) {
    CURL *handler = NULL;
    struct curl_slist *list = NULL;
    HttpResponse response = {.body_length=0, .raw_body=NULL, .header_length=0, .raw_header=NULL};

    __request_initialize(&handler, &list, &url, &header);
    curl_easy_setopt(handler, CURLOPT_NOBODY, 1);
    __request_execute(&handler, &response);
    __request_terminate(&handler, &list);

    return response;
}

HttpResponse http_options(const char *url, const char *data, HttpHeader header) {
    CURL *handler = NULL;
    struct curl_slist *list = NULL;
    HttpResponse response = {.body_length=0, .raw_body=NULL, .header_length=0, .raw_header=NULL};

    __request_initialize(&handler, &list, &url, &header);
    curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, "OPTIONS");
    curl_easy_setopt(handler, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(handler, CURLOPT_POSTFIELDSIZE, strlen(data));
    __request_execute(&handler, &response);
    __request_terminate(&handler, &list);

    return response;
}

HttpResponse http_patch(const char *url, const char *data, HttpHeader header) {
    CURL *handler = NULL;
    struct curl_slist *list = NULL;
    HttpResponse response = {.body_length=0, .raw_body=NULL, .header_length=0, .raw_header=NULL};

    __request_initialize(&handler, &list, &url, &header);
    curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(handler, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(handler, CURLOPT_POSTFIELDSIZE, strlen(data));
    __request_execute(&handler, &response);
    __request_terminate(&handler, &list);

    return response;
}

HttpResponse http_post(const char *url, const char *data, HttpHeader header) {
    CURL *handler = NULL;
    struct curl_slist *list = NULL;
    HttpResponse response = {.body_length=0, .raw_body=NULL, .header_length=0, .raw_header=NULL};

    __request_initialize(&handler, &list, &url, &header);
    curl_easy_setopt(handler, CURLOPT_HTTPPOST, 1);
    curl_easy_setopt(handler, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(handler, CURLOPT_POSTFIELDSIZE, strlen(data));
    __request_execute(&handler, &response);
    __request_terminate(&handler, &list);

    return response;
}

HttpResponse http_put(const char *url, const char *data, HttpHeader header) {
    CURL *handler = NULL;
    struct curl_slist *list = NULL;
    HttpResponse response = {.body_length=0, .raw_body=NULL, .header_length=0, .raw_header=NULL};

    __request_initialize(&handler, &list, &url, &header);
    curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(handler, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(handler, CURLOPT_POSTFIELDSIZE, strlen(data));
    __request_execute(&handler, &response);
    __request_terminate(&handler, &list);

    return response;
}

void http_response_delete(HttpResponse *response) {
    assert(NULL != response);
#define __X__(__key__)  \
    free((*response).header.__key__);
    __X_HTTP_HEADER__
#undef __X__
    free((*response).raw_header);
    free((*response).raw_body);
}

/************************************
 * Private functions definitions
 */
void __request_initialize(CURL **handler, struct curl_slist **list, const char **url, HttpHeader *header) {
    assert(NULL != handler);
    assert(NULL == *handler);
    assert(NULL != list);
    assert(NULL == *list);
    assert(NULL != url);
    assert(NULL != header);
    /* Setup curl handler */
    *handler = curl_easy_init();
    if (NULL == *handler) {
        perror(TRACE("Error"));
        abort();
    }
    /* Create the headers list */
    *list = __make_header(header);
#ifndef NDEBUG
    /* Get verbose debug output */
    curl_easy_setopt(*handler, CURLOPT_VERBOSE, 1L);
#endif
    /* Set request options */
    curl_easy_setopt(*handler, CURLOPT_URL, *url);
    curl_easy_setopt(*handler, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(*handler, CURLOPT_HTTPHEADER, *list);
    curl_easy_setopt(*handler, CURLOPT_HEADERFUNCTION, __header_callback);
    curl_easy_setopt(*handler, CURLOPT_WRITEFUNCTION, __response_callback);
}

void __request_execute(CURL **handler, HttpResponse *response) {
    assert(NULL != handler);
    assert(NULL != *handler);
    assert(NULL != response);
    /* Tell CURLOPT_HEADERFUNCTION where to write */
    curl_easy_setopt(*handler, CURLOPT_HEADERDATA, response);
    /* Tell CURLOPT_WRITEFUNCTION where to write */
    curl_easy_setopt(*handler, CURLOPT_WRITEDATA, response);
    /* Finally perform the request */
    CURLcode err = curl_easy_perform(*handler);
    if (CURLE_OK != err) {
        fprintf(stderr, TRACE("Error: %s\n"), curl_easy_strerror(err));
        abort();
    }
    /* Get the response HTTP status code */
    curl_easy_getinfo(*handler, CURLINFO_RESPONSE_CODE, &(*response).status);
    __parse_header(response);
}

void __request_terminate(CURL **handler, struct curl_slist **list) {
    assert(NULL != handler);
    assert(NULL != *handler);
    assert(NULL != list);
    assert(NULL != *list);
    curl_easy_cleanup(*handler);
    curl_slist_free_all(*list);
}

struct curl_slist *__make_header(HttpHeader *header) {
    assert(NULL != header);
    char key[SX_BUFFER_SIZE], buffer[LG_BUFFER_SIZE];
    struct curl_slist *header_list = NULL;
    /* X Macro trick to translate HttpHeader to corresponding string */
#define __X__(__key__)                                                          \
    if (NULL != (*header).__key__) {                                            \
        __from_underscore_to_hyphen(key, SX_BUFFER_SIZE, STR(__key__));         \
        snprintf(buffer, LG_BUFFER_SIZE, "%s: %s", key, (*header).__key__);     \
        header_list = curl_slist_append(header_list, buffer);                   \
    }
    __X_HTTP_HEADER__
#undef __X__
    return header_list;
}

void __parse_header(HttpResponse *response) {
    assert(NULL != response);
    struct phr_header headers[64];
    size_t headers_length = sizeof(headers) / sizeof(headers[0]);
    char buffer[LG_BUFFER_SIZE], xbuffer[LG_BUFFER_SIZE];
    const char *start = strchr((*response).raw_header, '\n') + 1;
    const int consumed = phr_parse_headers(start, (*response).header_length, headers, &headers_length, 0);
    if (consumed < 0) {
        return;
    }
    for (size_t i = 0; i < headers_length; i++) {
        snprintf(buffer, LG_BUFFER_SIZE, "%.*s", (int) headers[i].name_len, headers[i].name);
        /* X Macro trick to translate raw header string into corresponding HttpHeader */
#define __X__(__key__)                                                                                              \
        __from_underscore_to_hyphen(xbuffer, LG_BUFFER_SIZE, STR(__key__));                                         \
        if (strcmp(buffer, xbuffer) == 0) {                                                                         \
            if (NULL == (*response).header.__key__) {                                                               \
                (*response).header.__key__ = strndup(headers[i].value, headers[i].value_len);                       \
            } else {                                                                                                \
                const size_t n = snprintf(xbuffer, LG_BUFFER_SIZE, "%s, %.*s",                                      \
                                          (*response).header.__key__, (int) headers[i].value_len, headers[i].value  \
                );                                                                                                  \
                free((*response).header.__key__);                                                                   \
                (*response).header.__key__ = strndup(xbuffer, n);                                                   \
            }                                                                                                       \
            continue;                                                                                               \
        }
        __X_HTTP_HEADER__
#undef __X__
    }
}

size_t __header_callback(void *data, size_t size, size_t nmemb, HttpResponse *response) {
    const size_t actual_size = size * nmemb;
    /* realloc behaves like malloc if NULL is passed as arg */
    response->raw_header = realloc(response->raw_header, response->header_length + actual_size + 1); /* +1 for '\0' */
    if (NULL == response->raw_header) {
        perror(TRACE("Error"));
        abort();
    }
    memcpy(&response->raw_header[response->header_length], data, actual_size);
    response->header_length += actual_size;
    response->raw_header[response->header_length] = '\0';
    return actual_size;
}

size_t __response_callback(void *data, size_t size, size_t nmemb, HttpResponse *response) {
    const size_t actual_size = size * nmemb;
    /* realloc behaves like malloc if NULL is passed as arg */
    response->raw_body = realloc(response->raw_body, response->body_length + actual_size + 1); /* +1 for '\0' */
    if (NULL == response->raw_body) {
        perror(TRACE("Error"));
        abort();
    }
    memcpy(&response->raw_body[response->body_length], data, actual_size);
    response->body_length += actual_size;
    response->raw_body[response->body_length] = '\0';
    return actual_size;
}

void __from_underscore_to_hyphen(char *dst, size_t max, const char *src) {
    assert(NULL != dst);
    assert(NULL != src);
    size_t i = 0;
    while (i <= max && '\0' != src[i]) {
        dst[i] = (char) ('_' == src[i] ? '-' : src[i]);
        i += 1;
    }
    dst[i] = '\0';
}
