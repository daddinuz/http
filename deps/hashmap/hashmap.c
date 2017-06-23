/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   June 08, 2017
 * email:  daddinuz@gmail.com
 */

#include <math.h>
#include <errno.h>
#include <assert.h>

#include "hashmap_allocator.h"
#include "hashmap.h"

/*
 * Constant definitions
 */
static const double LOAD_FACTOR = 0.75;  /* MUST BE IN RANGE (0, 1) */

/*
 * Structures definitions
 */
typedef struct entry_t entry_t;

struct entry_t {
    int hash;
    void *key;
    void *value;
    entry_t *next;
};

struct hashmap_t {
    size_t size;
    size_t capacity;
    entry_t **buckets;
    int (*hash)(void *);
    bool (*equals)(void *, void *);
};

/*
 * Internal declarations
 */
static int __hash_key(hashmap_t *self, void *key);
static entry_t *__entry_new(int hash, void *key, void *value);
static size_t __calculate_index(size_t capacity, int hash);
static void __expand_if_necessary(hashmap_t *self);
static bool __is_equal(void *key_a, int hash_a, void *key_b, int hash_b, bool (*equals)(void *, void *));

/*
 * API definitions
 */
hashmap_pair_t *hashmap_pair_new(void *key, void *value) {
    hashmap_pair_t *pair = hashmap_m_malloc(sizeof(hashmap_pair_t));
    if (pair == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    pair->key = key;
    pair->value = value;
    return pair;
}

void hashmap_pair_delete(hashmap_pair_t *self) {
    assert(self != NULL);
    hashmap_m_free(self);
}

hashmap_t *hashmap_new(
        size_t initial_capacity,
        int (*hash)(void *),
        bool (*equals)(void *, void *)
) {
    assert(hash != NULL);
    assert(equals != NULL);

    hashmap_t *self = hashmap_m_malloc(sizeof(hashmap_t));
    if (self == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    self->size = 0;
    self->capacity = 1;
    self->hash = hash;
    self->equals = equals;

    const double minimum_capacity = ceil((1 + LOAD_FACTOR) * (double) initial_capacity);
    while (self->capacity <= minimum_capacity) {
        /* capacity must be power of 2. */
        self->capacity <<= 1;
    }

    self->buckets = hashmap_m_calloc(self->capacity, sizeof(entry_t *));
    if (self->buckets == NULL) {
        hashmap_m_free(self);
        errno = ENOMEM;
        return NULL;
    }

    return self;
}

void hashmap_clear(hashmap_t *self) {
    assert(self != NULL);
    for (size_t i = 0; i < self->capacity; i++) {
        entry_t *entry = self->buckets[i];
        while (entry != NULL) {
            entry_t *next = entry->next;
            hashmap_m_free(entry);
            entry = next;
        }
    }
    self->size = 0;
}

void hashmap_delete(hashmap_t *self) {
    assert(self != NULL);
    hashmap_clear(self);
    hashmap_m_free(self->buckets);
    hashmap_m_free(self);
}

void *hashmap_set(hashmap_t *self, void *key, void *value) {
    assert(self != NULL);
    int hash = __hash_key(self, key);
    size_t index = __calculate_index(self->capacity, hash);
    /* Pointer to the current entry. */
    entry_t **p = &(self->buckets[index]);
    while (true) {
        entry_t *current = *p;
        /* Add a new entry. */
        if (current == NULL) {
            *p = __entry_new(hash, key, value);
            if (*p == NULL) {
                errno = ENOMEM;
                return NULL;
            }
            self->size++;
            __expand_if_necessary(self);
            return NULL;
        }
        /* Replace existing entry. */
        if (__is_equal(current->key, current->hash, key, hash, self->equals)) {
            void *old_value = current->value;
            current->value = value;
            return old_value;
        }
        /* Move to next entry. */
        p = &current->next;
    }
}

void *hashmap_get(hashmap_t *self, void *key, void *default_value) {
    assert(self != NULL);
    int hash = __hash_key(self, key);
    size_t index = __calculate_index(self->capacity, hash);
    entry_t *entry = self->buckets[index];
    while (entry != NULL) {
        if (__is_equal(entry->key, entry->hash, key, hash, self->equals)) {
            return entry->value;
        }
        entry = entry->next;
    }
    return default_value;
}

bool hashmap_has(hashmap_t *self, void *key) {
    assert(self != NULL);
    int hash = __hash_key(self, key);
    size_t index = __calculate_index(self->capacity, hash);
    entry_t *entry = self->buckets[index];
    while (entry != NULL) {
        if (__is_equal(entry->key, entry->hash, key, hash, self->equals)) {
            return true;
        }
        entry = entry->next;
    }
    return false;
}

hashmap_pair_t *hashmap_remove(hashmap_t *self, void *key) {
    assert(self != NULL);
    int hash = __hash_key(self, key);
    size_t index = __calculate_index(self->capacity, hash);
    /* Pointer to the current entry. */
    entry_t **p = &(self->buckets[index]);
    entry_t *current;
    while ((current = *p) != NULL) {
        if (__is_equal(current->key, current->hash, key, hash, self->equals)) {
            hashmap_pair_t *pair = hashmap_pair_new(current->key, current->value);
            if (pair == NULL) {
                errno = ENOMEM;
                return NULL;
            }
            *p = current->next;
            hashmap_m_free(current);
            self->size--;
            return pair;
        }
        p = &current->next;
    }
    return NULL;
}

bool hashmap_empty(hashmap_t *self) {
    assert(self != NULL);
    return self->size == 0;
}

size_t hashmap_size(hashmap_t *self) {
    assert(self != NULL);
    return self->size;
}

size_t hashmap_capacity(hashmap_t *self) {
    assert(self != NULL);
    const double result = ceil(LOAD_FACTOR * (double) self->capacity);
    return (size_t) result;
}

void hashmap_each(hashmap_t *self, bool (*callback)(void *, void *, void *), void *context) {
    assert(self != NULL);
    for (size_t i = 0; i < self->capacity; i++) {
        entry_t *entry = self->buckets[i];
        while (entry != NULL) {
            entry_t *next = entry->next;
            if (!callback(entry->key, entry->value, context)) {
                return;
            }
            entry = next;
        }
    }
}

size_t hashmap_count_collisions(hashmap_t *self) {
    assert(self != NULL);
    size_t collisions = 0;
    for (size_t i = 0; i < self->capacity; i++) {
        entry_t *entry = self->buckets[i];
        while (entry != NULL) {
            if (entry->next != NULL) {
                collisions++;
            }
            entry = entry->next;
        }
    }
    return collisions;
}

/*
 * Internal definitions
 */
int __hash_key(hashmap_t *self, void *key) {
    assert(self != NULL);
    int h = self->hash(key);

    /*
     * We apply this secondary hashing discovered by Doug Lea
     * to defend against bad hashes.
     */
    h += ~(h << 9);
    h ^= (h >> 14);
    h += (h << 4);
    h ^= (h >> 10);

    return h;
}

entry_t *__entry_new(int hash, void *key, void *value) {
    entry_t *entry = hashmap_m_malloc(sizeof(entry_t));
    if (entry == NULL) {
        return NULL;
    }
    entry->hash = hash;
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    return entry;
}

size_t __calculate_index(size_t capacity, int hash) {
    return ((size_t) hash) & (capacity - 1);
}

void __expand_if_necessary(hashmap_t *self) {
    assert(self != NULL);
    if (self->size > floor(LOAD_FACTOR * (double) self->capacity)) {
        size_t new_capacity = self->capacity << 1;
        entry_t **new_buckets = hashmap_m_calloc(new_capacity, sizeof(entry_t *));
        if (new_buckets == NULL) {
            /* Abort expansion. */
            return;
        }
        /* Move over existing entries. */
        for (size_t i = 0; i < self->capacity; i++) {
            entry_t *entry = self->buckets[i];
            while (entry != NULL) {
                entry_t *next = entry->next;
                size_t index = __calculate_index(new_capacity, entry->hash);
                entry->next = new_buckets[index];
                new_buckets[index] = entry;
                entry = next;
            }
        }
        /* Copy over internals. */
        hashmap_m_free(self->buckets);
        self->buckets = new_buckets;
        self->capacity = new_capacity;
    }
}

bool __is_equal(void *key_a, int hash_a, void *key_b, int hash_b, bool (*equals)(void *, void *)) {
    if (key_a == key_b) {
        return true;
    }
    if (hash_a != hash_b) {
        return false;
    }
    return equals(key_a, key_b);
}
