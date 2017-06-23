/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 31, 2017 
 * email:  daddinuz@gmail.com
 */

#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "http_dict.h"
#include "hashmap.h"

#define INITIAL_CAPACITY 8

struct HttpDict {
    hashmap_t *pimpl;
};

/*
 * Private functions declarations
 */
static int __hash(void *key);
static bool __equals(void *key_a, void *key_b);

/*
 * API implementation
 */
HttpDict *http_dict_new(void) {
    HttpDict *self = malloc(sizeof(HttpDict));
    if (self == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    self->pimpl = hashmap_new(INITIAL_CAPACITY, __hash, __equals);
    if (self->pimpl == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    return self;
}

void http_dict_clear(HttpDict *self) {
    assert(self != NULL);
    hashmap_clear(self->pimpl);
}

void http_dict_delete(HttpDict *self) {
    assert(self != NULL);
    hashmap_delete(self->pimpl);
    free(self);
}

char *http_dict_set(HttpDict *self, char *key, char *value) {
    assert(self != NULL);
    return hashmap_set(self->pimpl, key, value);
}

char *http_dict_get(HttpDict *self, char *key, char *default_value) {
    assert(self != NULL);
    return hashmap_get(self->pimpl, key, default_value);
}

bool http_dict_has(HttpDict *self, char *key) {
    assert(self != NULL);
    return hashmap_has(self->pimpl, key);
}

HttpPair *http_dict_remove(HttpDict *self, char *key) {
    assert(self != NULL);
    hashmap_pair_t *pair = hashmap_remove(self->pimpl, key);
    void *k = pair->key;
    void *v = pair->value;
    hashmap_pair_delete(pair);
    return http_pair_new(k, v);
}

bool http_dict_empty(HttpDict *self) {
    assert(self != NULL);
    return hashmap_empty(self->pimpl);
}

size_t http_dict_size(HttpDict *self) {
    assert(self != NULL);
    return hashmap_size(self->pimpl);
}

void http_dict_each(HttpDict *self, bool (*callback)(char *key, char *value, void *context), void *context) {
    assert(self != NULL);
    bool (*fn)(void *, void *, void *) = (bool (*)(void *, void *, void *)) callback;
    hashmap_each(self->pimpl, fn, context);
}

/*
 * Private functions definitions
 */
int __hash(void *key) {
    int hash = 0;
    char *data = key;
    while (*data) {
        hash += *data;
        hash += (hash << 10);
        hash ^= (hash >> 6);
        data++;
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

bool __equals(void *key_a, void *key_b) {
    return strcmp((const char *const) key_a, (const char *const) key_b) == 0;
}
