/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 28, 2017 
 * email:  daddinuz@gmail.com
 */

#include <stdlib.h>
#include <string.h>
#include "http_string.h"

static char *__http_string_init(size_t size) {
    return calloc(size + 1, sizeof(char));
}

HttpString http_string_new(const char *text) {
    return text ? strdup(text) : NULL;
}

void http_string_delete(HttpString self) {
    free((void *) self);
}

HttpString http_string_join(const char *a, const char *b) {
    const size_t size = strlen(a) + strlen(b);
    char *self = __http_string_init(size);
    strcpy(self, a);
    strcat(self, b);
    return self;
}
