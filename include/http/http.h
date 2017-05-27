/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmal.com
 */

#include <stdbool.h>
#include "http_dict.h"
#include "http_status.h"
#include "http_method.h"
#include "http_request.h"
#include "http_response.h"

#ifndef __HTTP_H__
#define __HTTP_H__

#define HTTP_VERSION "0.2.0"

#ifdef __cplusplus
extern "C" {
#endif

extern HttpResponse http_perform(HttpRequest request, bool allow_redirects, long timeout);

#define http_x_no_params  0

typedef struct HttpXParams {
    long timeout;
    bool allow_redirects;
    HttpDictEntry *headers;
    char *body;
} HttpXParams;

extern HttpResponse __http_get(const char *url, HttpXParams x_params);
#define http_get(url, ...)        __http_get(url, (HttpXParams) {__VA_ARGS__})

extern HttpResponse __http_head(const char *url, HttpXParams x_params);
#define http_head(url, ...)       __http_head(url, (HttpXParams) {__VA_ARGS__})

extern HttpResponse __http_delete(const char *url, HttpXParams x_params);
#define http_delete(url, ...)     __http_delete(url, (HttpXParams) {__VA_ARGS__})

extern HttpResponse __http_options(const char *url, HttpXParams x_params);
#define http_options(url, ...)    __http_options(url, (HttpXParams) {__VA_ARGS__})

extern HttpResponse __http_put(const char *url, HttpXParams x_params);
#define http_put(url, ...)        __http_put(url, (HttpXParams) {__VA_ARGS__})

extern HttpResponse __http_post(const char *url, HttpXParams x_params);
#define http_post(url, ...)       __http_post(url, (HttpXParams) {__VA_ARGS__})

extern HttpResponse __http_patch(const char *url, HttpXParams x_params);
#define http_patch(url, ...)      __http_patch(url, (HttpXParams) {__VA_ARGS__})

#ifdef __cplusplus
}
#endif

#endif
