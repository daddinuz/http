/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   June 22, 2017 
 * email:  daddinuz@gmal.com
 */

#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include "http_pair.h"
#include "hashmap.h"

struct HttpPair {
    hashmap_pair_t *pimpl;
};

HttpPair *http_pair_new(char *key, char *value) {
    HttpPair *self = malloc(sizeof(HttpPair));
    if (self == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    self->pimpl = hashmap_pair_new(key, value);
    if (self->pimpl == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    return self;
}

void http_pair_delete(HttpPair *self) {
    assert(self != NULL);
    hashmap_pair_delete(self->pimpl);
    free(self);
}

char *http_pair_key(HttpPair *self) {
    assert(self != NULL);
    return self->pimpl->key;
}

char *http_pair_value(HttpPair *self) {
    assert(self != NULL);
    return self->pimpl->value;
}
