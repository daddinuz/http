/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 28, 2017 
 * email:  daddinuz@gmal.com
 */

#include <stdlib.h>
#include <string.h>
#include "http_string.h"

HttpString http_string_new(const char *str) {
    return strdup(str);
}

void http_string_delete(HttpString **ref) {
    if (ref && *ref) {
        free(*ref);
        *ref = NULL;
    }
}
