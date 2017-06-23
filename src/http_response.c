/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017
 * email:  daddinuz@gmail.com
 */

#include <stdlib.h>
#include <string.h>
#include "http_response.h"

const HttpResponse *http_response_new(
        const HttpRequest *request,
        int status_code,
        HttpString url,
        HttpString raw_headers,
        size_t headers_length,
        HttpString raw_body,
        size_t body_length
) {
    HttpResponse initializer = {
            .request=(HttpRequest *) request,
            .status_code=status_code,
            .url=url,
            .raw_headers=raw_headers,
            .headers_length=headers_length,
            .raw_body=raw_body,
            .body_length=body_length
    };
    HttpResponse *response = malloc(sizeof(HttpResponse));
    memcpy(response, &initializer, sizeof(HttpResponse));
    return response;
}

void http_response_delete(const HttpResponse *self) {
    if (self) {
        http_string_delete(self->url);
        http_string_delete(self->raw_headers);
        http_string_delete(self->raw_body);
    }
    free((HttpResponse *) self);
}
