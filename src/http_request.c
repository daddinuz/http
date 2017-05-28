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

HttpRequest *http_request_new(
        const HttpString method,
        const HttpString url,
        const HttpDictEntry *headers,
        const HttpString body
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

void http_request_delete(HttpRequest **ref) {
    if (ref && *ref) {
        free(*ref);
        *ref = NULL;
    }
}
