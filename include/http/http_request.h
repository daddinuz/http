/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017 
 * email:  daddinuz@gmail.com
 */

#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include "http_method.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * http_request_t opaque type.
 */
typedef struct http_request {
    const http_method_t method;
    const char *url;
    const char *headers;
    const char *body;
} http_request_t;

/**
 * Create a new `http_request_t *` instance.
 * If memory allocation fails, this function returns NULL, and errno is set to ENOMEM.
 *
 * @param method The HTTP request method.
 * @param url The HTTP request URL.
 * @param headers The HTTP request headers.
 * @param body The HTTP request body.
 * @return A new `http_request_t *` instance.
 */
extern http_request_t *http_request_new(
        http_method_t method,
        const char *url,
        const char *headers,
        const char *body
);

/**
 * Delete an already created `http_request_t *` instance.
 *
 * @param self The `http_request_t *` instance.
 */
extern void http_request_delete(http_request_t *self);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_REQUEST_H__ */
