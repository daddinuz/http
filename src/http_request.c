/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017 
 * email:  daddinuz@gmail.com
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "http_method.h"
#include "http_request.h"

http_request_t *http_request_new(
        const http_method_t method,
        const char *const url,
        const char *const headers,
        const char *const body
) {
    struct http_request *self = malloc(sizeof(http_request_t));
    if (NULL == self) {
        errno = ENOMEM;
        return NULL;
    }
    const http_request_t initializer = {
            .method=method,
            .url=url,
            .headers=headers,
            .body=body
    };
    memcpy(self, &initializer, sizeof(http_request_t));
    return self;
}

void http_request_delete(http_request_t *self) {
    free((void *) self);
}
