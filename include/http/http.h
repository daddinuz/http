/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmal.com
 */

#include <stddef.h>
#include "http_status.h"
#include "http_method.h"
#include "http_header.h"

#ifndef __HTTP_H__
#define __HTTP_H__

#define HTTP_VERSION "0.1.0"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * Data structures definitions
 */
typedef struct HttpResponse {
    HttpStatus status;
    HttpHeader header;
    char *raw_header;
    char *raw_body;
    size_t header_length;
    size_t body_length;
} HttpResponse;

/*********************************
 * Prototypes
 */
extern HttpResponse http_delete(const char *url, const char *data, HttpHeader header);
extern HttpResponse http_get(const char *url, HttpHeader header);
extern HttpResponse http_head(const char *url, HttpHeader header);
extern HttpResponse http_options(const char *url, const char *data, HttpHeader header);
extern HttpResponse http_patch(const char *url, const char *data, HttpHeader header);
extern HttpResponse http_post(const char *url, const char *data, HttpHeader header);
extern HttpResponse http_put(const char *url, const char *data, HttpHeader header);

extern void http_response_delete(HttpResponse *response);

#ifdef __cplusplus
}
#endif

#endif
