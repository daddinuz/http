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
#include "http_request.h"

const HttpRequest *http_request_new(
        HttpString method,
        HttpString url,
        HttpDict *headers,
        HttpString body
) {
    HttpRequest *self = malloc(sizeof(HttpRequest));
    if (NULL == self) {
        errno = ENOMEM;
        return NULL;
    }
    HttpRequest initializer = {
            .method=method,
            .url=url,
            .headers=headers,
            .body=body
    };
    memcpy(self, &initializer, sizeof(HttpRequest));
    return self;
}

void http_request_delete(const HttpRequest *self) {
    free((HttpRequest *) self);
}
