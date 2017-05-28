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

HttpRequest *http_request_bake(
        HttpString method,
        HttpString url,
        const HttpDictEntry *headers,
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

HttpRequest *http_request_new(
        const char *method,
        const char *url,
        const HttpDictEntry *headers,
        const char *body
) {
    return http_request_bake(
            http_string_new(method),
            http_string_new(url),
            headers,
            http_string_new(body)
    );
}

void http_request_delete(HttpRequest *self) {
    if (self) {
        http_string_delete(self->method);
        http_string_delete(self->url);
        http_string_delete(self->body);
    }
    free(self);
}
