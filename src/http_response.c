/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017
 * email:  daddinuz@gmal.com
 */

#include <stdlib.h>
#include <string.h>
#include "http_response.h"

HttpResponse *http_response_bake(
        HttpRequest *request,
        int status_code,
        HttpString url,
        HttpString raw_headers,
        size_t headers_length,
        HttpString raw_body,
        size_t body_length
) {
    HttpResponse initializer = {
            .request=request,
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

HttpResponse *http_response_new(
        HttpRequest *request,
        int status_code,
        const char *url,
        const char *raw_headers,
        const char *raw_body
) {
    return http_response_bake(
            request,
            status_code,
            http_string_new(url),
            http_string_new(raw_headers),
            strlen(raw_headers),
            http_string_new(raw_body),
            strlen(raw_body)
    );
}

void http_response_delete(HttpResponse *self) {
    if (self) {
        http_string_delete(self->url);
        http_string_delete(self->raw_headers);
        http_string_delete(self->raw_body);
    }
    free(self);
}
