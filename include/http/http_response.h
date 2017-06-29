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
struct http_response {
    const int status;
    http_request_t *const request;
    const char *const url;
    const char *const headers;
    const char *const body;
};

typedef const struct http_response http_response_t;

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
