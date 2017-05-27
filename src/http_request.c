/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017 
 * email:  daddinuz@gmal.com
 */

#include "http_request.h"

HttpRequest http_request_create(
        const char *method,
        const char *url,
        HttpDict headers,
        const char *body
) {
    return (HttpRequest) {
            .method=(char *) method,
            .url=(char *) url,
            .headers=headers,
            .body=(char *) body
    };
}
