/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmail.com
 */

#ifndef __HTTP_H__
#define __HTTP_H__

#define HTTP_VERSION "0.2.5"

#include <stdbool.h>
#include "http_dict.h"
#include "http_string.h"
#include "http_status.h"
#include "http_method.h"
#include "http_request.h"
#include "http_response.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Structure holding request parameters
 */
typedef struct HttpParams {
    int __sentinel__;
    HttpDict *headers;
    HttpString body;
    bool no_follow_location;
    bool no_peer_verification;
    bool no_host_verification;
    long timeout;
} HttpParams;

/**
 * Compose and send an HTTP request.
 *
 * @param method Request HttpMethod
 * @param url URL to call
 * @param params Request parameters
 * @return The HttpResponse related to the sent request
 */
extern const HttpResponse *http_request(HttpString method, HttpString url, HttpParams *params);

#define http_get(url, ...)      http_request(HTTP_METHOD.GET, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_head(url, ...)     http_request(HTTP_METHOD.HEAD, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_delete(url, ...)   http_request(HTTP_METHOD.DELETE, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_options(url, ...)  http_request(HTTP_METHOD.OPTIONS, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_put(url, ...)      http_request(HTTP_METHOD.PUT, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_post(url, ...)     http_request(HTTP_METHOD.POST, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_patch(url, ...)    http_request(HTTP_METHOD.PATCH, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_H__ */
