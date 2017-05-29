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

#define HTTP_VERSION "0.2.3"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HttpParams {
    int __sentinel__;
    const char *url;
    HttpDictEntry *headers;
    const char *body;
    bool no_follow_location;
    bool no_peer_verification;
    bool no_host_verification;
    long timeout;
} HttpParams;

#define http_request(method, ...)   __http_perform(__FILE__, __LINE__, method, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_get(...)               __http_perform(__FILE__, __LINE__, HttpMethod.GET, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_head(...)              __http_perform(__FILE__, __LINE__, HttpMethod.HEAD, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_delete(...)            __http_perform(__FILE__, __LINE__, HttpMethod.DELETE, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_options(...)           __http_perform(__FILE__, __LINE__, HttpMethod.OPTIONS, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_put(...)               __http_perform(__FILE__, __LINE__, HttpMethod.PUT, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_post(...)              __http_perform(__FILE__, __LINE__, HttpMethod.POST, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})
#define http_patch(...)             __http_perform(__FILE__, __LINE__, HttpMethod.PATCH, &(HttpParams) {.__sentinel__=0, __VA_ARGS__})

extern HttpResponse *__http_perform(const char *file, int line, HttpString method, HttpParams *params);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_H__ */
