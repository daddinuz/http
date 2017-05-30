/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmal.com
 */

#include <stdbool.h>
#include "http_dict.h"
#include "http_string.h"
#include "http_status.h"
#include "http_method.h"
#include "http_request.h"
#include "http_response.h"

#ifndef __HTTP_H__
#define __HTTP_H__

#define HTTP_VERSION "0.2.4"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HttpParams {
    int __sentinel__;
    HttpDictEntry *headers;
    const char *body;
    bool no_follow_location;
    bool no_peer_verification;
    bool no_host_verification;
    long timeout;
} HttpParams;

extern HttpResponse *http_request(HttpString method, HttpString url, HttpParams *params);

#define http_get(url, ...)      http_request(HttpMethod.GET, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_head(url, ...)     http_request(HttpMethod.HEAD, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_delete(url, ...)   http_request(HttpMethod.DELETE, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_options(url, ...)  http_request(HttpMethod.OPTIONS, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_put(url, ...)      http_request(HttpMethod.PUT, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_post(url, ...)     http_request(HttpMethod.POST, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_patch(url, ...)    http_request(HttpMethod.PATCH, url, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_H__ */
