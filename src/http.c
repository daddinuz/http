/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017
 * email:  daddinuz@gmail.com
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <curl/curl.h>
#include "http.h"

typedef struct {
    size_t size;
    char *memory;
} buffer_t;

static const char *const __HTTP_METHOD_DELETE = "DELETE";
static const char *const __HTTP_METHOD_GET = "GET";
static const char *const __HTTP_METHOD_HEAD = "HEAD";
static const char *const __HTTP_METHOD_POST = "POST";
static const char *const __HTTP_METHOD_PUT = "PUT";
static const char *const __HTTP_METHOD_CONNECT = "CONNECT";
static const char *const __HTTP_METHOD_OPTIONS = "OPTIONS";
static const char *const __HTTP_METHOD_TRACE = "TRACE";
static const char *const __HTTP_METHOD_COPY = "COPY";
static const char *const __HTTP_METHOD_LOCK = "LOCK";
static const char *const __HTTP_METHOD_MKCOL = "MKCOL";
static const char *const __HTTP_METHOD_MOVE = "MOVE";
static const char *const __HTTP_METHOD_PROPFIND = "PROPFIND";
static const char *const __HTTP_METHOD_PROPPATCH = "PROPPATCH";
static const char *const __HTTP_METHOD_SEARCH = "SEARCH";
static const char *const __HTTP_METHOD_UNLOCK = "UNLOCK";
static const char *const __HTTP_METHOD_BIND = "BIND";
static const char *const __HTTP_METHOD_REBIND = "REBIND";
static const char *const __HTTP_METHOD_UNBIND = "UNBIND";
static const char *const __HTTP_METHOD_ACL = "ACL";
static const char *const __HTTP_METHOD_REPORT = "REPORT";
static const char *const __HTTP_METHOD_MKACTIVITY = "MKACTIVITY";
static const char *const __HTTP_METHOD_CHECKOUT = "CHECKOUT";
static const char *const __HTTP_METHOD_MERGE = "MERGE";
static const char *const __HTTP_METHOD_MSEARCH = "M-SEARCH";
static const char *const __HTTP_METHOD_NOTIFY = "NOTIFY";
static const char *const __HTTP_METHOD_SUBSCRIBE = "SUBSCRIBE";
static const char *const __HTTP_METHOD_UNSUBSCRIBE = "UNSUBSCRIBE";
static const char *const __HTTP_METHOD_PATCH = "PATCH";
static const char *const __HTTP_METHOD_PURGE = "PURGE";
static const char *const __HTTP_METHOD_MKCALENDAR = "MKCALENDAR";
static const char *const __HTTP_METHOD_LINK = "LINK";
static const char *const __HTTP_METHOD_UNLINK = "UNLINK";

static http_response_t *__http_response_new(
        const http_request_t *request,
        const char *url,
        const char *headers,
        const char *body,
        const size_t headers_length,
        const size_t body_length,
        int status
);
static const char *__http_method_to_string(http_method_t method);
static void __die(const char *file, int line, const char *message);
static size_t __callback(void *content, size_t member_size, size_t members_count, void *user_data);

http_response_t *http_perform(http_request_t *request, http_params_t *params) {
    assert(request);
    int status_code = 0;
    buffer_t body_buffer = {0};
    buffer_t headers_buffer = {0};
    const char *effective_url = NULL;
    struct curl_slist *headers_list = NULL;
    CURL *handler = curl_easy_init();

    /* Set request url and method */
    curl_easy_setopt(handler, CURLOPT_URL, request->url);
    curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, __http_method_to_string(request->method));

    /* Set request headers */
    if (request->headers) {
        headers_list = curl_slist_append(headers_list, request->headers);
        curl_easy_setopt(handler, CURLOPT_HTTPHEADER, headers_list);
    }

    /* Set request body */
    if (request->body) {
        curl_easy_setopt(handler, CURLOPT_POSTFIELDS, request->body);
        curl_easy_setopt(handler, CURLOPT_POSTFIELDSIZE, strlen(request->body));
    }

    /* Set request parameters */
    if (params) {
        curl_easy_setopt(handler, CURLOPT_FOLLOWLOCATION, !params->no_follow_location);
        curl_easy_setopt(handler, CURLOPT_SSL_VERIFYPEER, !params->no_peer_verification);
        curl_easy_setopt(handler, CURLOPT_SSL_VERIFYHOST, !params->no_host_verification);
        if (params->timeout > 0) {
            curl_easy_setopt(handler, CURLOPT_TIMEOUT, params->timeout);
        }
    }

    /* Set request callbacks in order to store the response data */
    curl_easy_setopt(handler, CURLOPT_HEADERFUNCTION, __callback);
    curl_easy_setopt(handler, CURLOPT_HEADERDATA, &headers_buffer);
    curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, __callback);
    curl_easy_setopt(handler, CURLOPT_WRITEDATA, &body_buffer);

#ifndef NDEBUG
    /* Set verbose debug output */
    curl_easy_setopt(handler, CURLOPT_VERBOSE, 1L);
#endif

    /* Perform the request */
    CURLcode curl_errno = curl_easy_perform(handler);
    if (CURLE_OK != curl_errno) {
        __die(__FILE__, __LINE__, curl_easy_strerror(curl_errno));
    }

    /* Get response's info */
    curl_easy_getinfo(handler, CURLINFO_RESPONSE_CODE, &status_code);
    if (params && params->no_follow_location) {
        effective_url = strdup(request->url);
    } else {
        char *tmp = NULL;
        curl_easy_getinfo(handler, CURLINFO_EFFECTIVE_URL, &tmp);
        effective_url = strdup(tmp);
    }

    /* Terminate */
    curl_slist_free_all(headers_list);
    curl_easy_cleanup(handler);

    return __http_response_new(
            request,
            effective_url,
            headers_buffer.memory,
            body_buffer.memory,
            headers_buffer.size,
            body_buffer.size,
            status_code
    );
}

http_response_t *__http_response_new(
        const http_request_t *request,
        const char *url,
        const char *headers,
        const char *body,
        const size_t headers_length,
        const size_t body_length,
        int status
) {
    struct http_response *self = malloc(sizeof(http_response_t));
    if (NULL == self) {
        errno = ENOMEM;
        return NULL;
    }
    const http_response_t initializer = {
            .request=request,
            .url=url,
            .headers=headers,
            .body=body,
            .headers_length=headers_length,
            .body_length=body_length,
            .status=status
    };
    memcpy(self, &initializer, sizeof(http_response_t));
    return self;
}

const char *__http_method_to_string(http_method_t method) {
    switch (method) {
        case HTTP_METHOD_DELETE:
            return __HTTP_METHOD_DELETE;
        case HTTP_METHOD_GET:
            return __HTTP_METHOD_GET;
        case HTTP_METHOD_HEAD:
            return __HTTP_METHOD_HEAD;
        case HTTP_METHOD_POST:
            return __HTTP_METHOD_POST;
        case HTTP_METHOD_PUT:
            return __HTTP_METHOD_PUT;
        case HTTP_METHOD_CONNECT:
            return __HTTP_METHOD_CONNECT;
        case HTTP_METHOD_OPTIONS:
            return __HTTP_METHOD_OPTIONS;
        case HTTP_METHOD_TRACE:
            return __HTTP_METHOD_TRACE;
        case HTTP_METHOD_COPY:
            return __HTTP_METHOD_COPY;
        case HTTP_METHOD_LOCK:
            return __HTTP_METHOD_LOCK;
        case HTTP_METHOD_MKCOL:
            return __HTTP_METHOD_MKCOL;
        case HTTP_METHOD_MOVE:
            return __HTTP_METHOD_MOVE;
        case HTTP_METHOD_PROPFIND:
            return __HTTP_METHOD_PROPFIND;
        case HTTP_METHOD_PROPPATCH:
            return __HTTP_METHOD_PROPPATCH;
        case HTTP_METHOD_SEARCH:
            return __HTTP_METHOD_SEARCH;
        case HTTP_METHOD_UNLOCK:
            return __HTTP_METHOD_UNLOCK;
        case HTTP_METHOD_BIND:
            return __HTTP_METHOD_BIND;
        case HTTP_METHOD_REBIND:
            return __HTTP_METHOD_REBIND;
        case HTTP_METHOD_UNBIND:
            return __HTTP_METHOD_UNBIND;
        case HTTP_METHOD_ACL:
            return __HTTP_METHOD_ACL;
        case HTTP_METHOD_REPORT:
            return __HTTP_METHOD_REPORT;
        case HTTP_METHOD_MKACTIVITY:
            return __HTTP_METHOD_MKACTIVITY;
        case HTTP_METHOD_CHECKOUT:
            return __HTTP_METHOD_CHECKOUT;
        case HTTP_METHOD_MERGE:
            return __HTTP_METHOD_MERGE;
        case HTTP_METHOD_MSEARCH:
            return __HTTP_METHOD_MSEARCH;
        case HTTP_METHOD_NOTIFY:
            return __HTTP_METHOD_NOTIFY;
        case HTTP_METHOD_SUBSCRIBE:
            return __HTTP_METHOD_SUBSCRIBE;
        case HTTP_METHOD_UNSUBSCRIBE:
            return __HTTP_METHOD_UNSUBSCRIBE;
        case HTTP_METHOD_PATCH:
            return __HTTP_METHOD_PATCH;
        case HTTP_METHOD_PURGE:
            return __HTTP_METHOD_PURGE;
        case HTTP_METHOD_MKCALENDAR:
            return __HTTP_METHOD_MKCALENDAR;
        case HTTP_METHOD_LINK:
            return __HTTP_METHOD_LINK;
        case HTTP_METHOD_UNLINK:
            return __HTTP_METHOD_UNLINK;
        default:
            __die(__FILE__, __LINE__, "Unknown HTTP method");
            return NULL;
    }
}

void __die(const char *file, int line, const char *message) {
    fprintf(stderr, "\nAt: %s:%d\nError: %s\n", file, line, message);
    abort();
}

size_t __callback(void *content, size_t member_size, size_t members_count, void *user_data) {
    buffer_t *const buffer = user_data;
    const size_t real_size = member_size * members_count;

    buffer->memory = realloc(buffer->memory, buffer->size + real_size + 1);
    if (NULL == buffer->memory) {
        __die(__FILE__, __LINE__, strerror(errno));
    }

    memcpy(&(buffer->memory[buffer->size]), content, real_size);
    buffer->size += real_size;
    buffer->memory[buffer->size] = 0;

    return real_size;
}
