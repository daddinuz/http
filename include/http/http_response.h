/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017 
 * email:  daddinuz@gmail.com
 */

#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include "http_request.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * http_response_t opaque type.
 */
typedef struct http_response {
    const int status;
    const http_request_t *request;
    const char *url;
    const char *headers;
    const char *body;
} http_response_t;

/**
 * Create a new `http_response_t *` instance.
 * If memory allocation fails, this function returns NULL, and errno is set to ENOMEM.
 *
 * @param status The response HTTP status code.
 * @param request The associated HTTP request.
 * @param url The effective URL called.
 * @param headers The response HTTP headers.
 * @param body The response HTTP body.
 * @return A new `http_response_t *` instance.
 */
extern http_response_t *http_response_new(
        int status,
        const http_request_t *request,
        const char *url,
        const char *headers,
        const char *body
);

/**
 * Delete an already created `http_response_t *` instance.
 *
 * @param self The `http_response_t *` instance.
 */
extern void http_response_delete(http_response_t *self);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_RESPONSE_H__ */
