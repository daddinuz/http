/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017 
 * email:  daddinuz@gmal.com
 */

#include <stdlib.h>
#include "http_response.h"

HttpResponse http_response_create(
        int status_code,
        const char *url,
        const char *headers,
        size_t headers_length,
        const char *body,
        size_t body_length
) {
    return (HttpResponse) {
            .status_code=status_code,
            .url=(char *) url,
            .headers=(char *) headers,
            .headers_length=headers_length,
            .body=(char *) body,
            .body_length=body_length
    };
}

void http_response_destroy(HttpResponse *response) {
    if (response) {
        free((*response).url);
        free((*response).headers);
        free((*response).body);
    }
}
