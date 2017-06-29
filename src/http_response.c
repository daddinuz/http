/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017
 * email:  daddinuz@gmail.com
 */

#include <stdlib.h>
#include "http_response.h"

void http_response_delete(http_response_t *self) {
    if (self) {
        free((void *) self->url);
        free((void *) self->headers);
        free((void *) self->body);
        free((void *) self);
    }
}
