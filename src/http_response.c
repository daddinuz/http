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

HttpResponse *http_response_new(
        const HttpRequest *request,
        int status_code,
        const HttpString url,
        const HttpString raw_headers,
        size_t headers_length,
        const HttpString raw_body,
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

void http_response_delete(HttpResponse **ref) {
    if (ref && *ref) {
        http_request_delete((HttpRequest **) &(**ref).request);
        free((void *) (**ref).url);
        free((void *) (**ref).raw_headers);
        free((void *) (**ref).raw_body);
        free(*ref);
        *ref = NULL;
    }
}
