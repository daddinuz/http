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
#include "http_response.h"

http_response_t *http_response_new(
        int status,
        const http_request_t *request,
        const char *url,
        const char *headers,
        const char *body
) {
    http_response_t *self = malloc(sizeof(http_response_t));
    if (NULL == self) {
        errno = ENOMEM;
        return NULL;
    }
    http_response_t initializer = {
            .request=request,
            .status=status,
            .url=url,
            .headers=headers,
            .body=body
    };
    memcpy(self, &initializer, sizeof(http_response_t));
    return self;
}

void http_response_delete(http_response_t *self) {
    if (self) {
        free((void *) self->url);
        free((void *) self->headers);
        free((void *) self->body);
        free(self);
    }
}
