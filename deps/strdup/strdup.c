/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   February 12, 2017 
 * email:  daddinuz@gmal.com
 */

#include <stdlib.h>
#include <string.h>
#include "strdup.h"


/*********************************
 * Public functions definitions
 */
char *strdup(const char *s) {
    return strndup(s, strlen(s));
}

char *strndup(const char *s, size_t n) {
    if (NULL == s) {
        return NULL;
    }
    char *buffer = calloc(n + 1, sizeof(char));
    if (NULL != buffer) {
        strncpy(buffer, s, n);
    }
    return buffer;
}
