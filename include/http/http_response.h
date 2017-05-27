/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017 
 * email:  daddinuz@gmal.com
 */

#include <stddef.h>

#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HttpResponse {
    int status_code;        /* HTTP status response code. */
    char *url;              /* URL where has been sent. */
    char *headers;          /* Response headers. */
    size_t headers_length;  /* Headers length */
    char *body;             /* Response body. */
    size_t body_length;     /* Body length */
} HttpResponse;

extern HttpResponse http_response_create(
        int status_code,
        const char *url,
        const char *headers,
        size_t headers_length,
        const char *body,
        size_t body_length
);

extern void http_response_destroy(HttpResponse *response);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_RESPONSE_H__ */
