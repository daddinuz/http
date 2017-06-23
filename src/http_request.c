/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017 
 * email:  daddinuz@gmal.com
 */

#include <stdlib.h>
#include <string.h>
#include "http_request.h"

const HttpRequest *http_request_new(
        HttpString method,
        HttpString url,
        HttpDict *headers,
        HttpString body
) {
    HttpRequest initializer = {
            .method=method,
            .url=url,
            .headers=headers,
            .body=body
    };
    HttpRequest *request = malloc(sizeof(HttpRequest));
    memcpy(request, &initializer, sizeof(HttpRequest));
    return request;
}

void http_request_delete(const HttpRequest *self) {
    free((HttpRequest *) self);
}
