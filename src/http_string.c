/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 28, 2017 
 * email:  daddinuz@gmail.com
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "http_string.h"

/*
 * Private functions declarations
 */
static char *__http_string_init(size_t size);

/*
 * API functions definitions
 */
HttpString http_string_new(size_t size) {
    return __http_string_init(size);
}

HttpString http_string_copy(const char *text) {
    char *self = NULL;
    if (text) {
        self = strdup(text);
        if (NULL == self) {
            errno = ENOMEM;
        }
    }
    return self;
}

HttpString http_string_join(const char *a, const char *b) {
    const char *safe_a = a ? a : "";
    const char *safe_b = b ? b : "";
    const size_t size = strlen(safe_a) + strlen(safe_b);
    char *self = __http_string_init(size);
    if (NULL == self) {
        errno = ENOMEM;
        return NULL;
    }
    strcpy(self, safe_a);
    strcat(self, safe_b);
    return self;
}

void http_string_delete(HttpString self) {
    assert(self);
    free((void *) self);
}

/*
 * Private functions definitions
 */
char *__http_string_init(size_t size) {
    char *self = calloc(size + 1, sizeof(char));
    if (NULL == self) {
        errno = ENOMEM;
    }
    return self;
}
