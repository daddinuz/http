/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017 
 * email:  daddinuz@gmal.com
 */

#include <stddef.h>
#include "http_request.h"

#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HttpResponse {
    const HttpRequest *request;   /* Related HTTP request */
    const int status_code;        /* HTTP status response code. */
    const HttpString url;         /* URL where has been sent. */
    const HttpString raw_headers; /* Response raw headers. */
    const HttpString raw_body;    /* Response raw_body. */
    const size_t headers_length;  /* Headers length */
    const size_t body_length;     /* Body length */
} HttpResponse;

extern HttpResponse *http_response_new(
        const HttpRequest *request,
        int status_code,
        const HttpString url,
        const HttpString raw_headers,
        size_t headers_length,
        const HttpString raw_body,
        size_t body_length
);

extern void http_response_delete(HttpResponse **ref);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_RESPONSE_H__ */
