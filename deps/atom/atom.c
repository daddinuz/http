/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <alligator/alligator.h>
#include "atom.h"

#define ATOM_TABLE_SIZE 2039

struct Atom_Node {
    struct Atom_Node *next;
    size_t length;
    uint32_t hash;
    void *bytes;
};

static uint32_t
Atom_hash(const void *bytes, size_t length)
__attribute__((__warn_unused_result__, __nonnull__));

static struct Atom_Node *
Atom_put(const void *bytes, size_t length, uint32_t hash)
__attribute__((__warn_unused_result__, __nonnull__));

static struct Atom_Node *
Atom_fetch(const void *bytes, size_t length, uint32_t hash)
__attribute__((__warn_unused_result__, __nonnull__));

static void
Atom_onExit(void);

static void
Atom_assertValidInstance(Atom atom)
__attribute__((__nonnull__));

static bool initialized = false;
static struct Atom_Node *table[ATOM_TABLE_SIZE] = {0};

/*
 *
 */
Atom Atom_fromBytes(const void *const bytes, const size_t length) {
    assert(bytes);
    assert(length < SIZE_MAX);
    return Atom_put(bytes, length, Atom_hash(bytes, length))->bytes;
}

Atom Atom_fromLiteral(const char *const literal) {
    assert(literal);
    assert(strlen(literal) < SIZE_MAX);
    return Atom_fromBytes(literal, strlen(literal));
}

Atom Atom_fromInteger(const long long number) {
    char buffer[64] = {0};
    const size_t bufferSize = sizeof(buffer) / sizeof(buffer[0]);
    const int length = snprintf(buffer, bufferSize, "%lld", number);
    assert(0 < length && length < (int) bufferSize);
    return Atom_fromBytes(buffer, (size_t) length);
}

Atom Atom_fromFloating(const long double number) {
    char buffer[64] = {0};
    const size_t bufferSize = sizeof(buffer) / sizeof(buffer[0]);
    const int length = snprintf(buffer, bufferSize, "%.8Lf", number);
    assert(0 < length && length < (int) bufferSize);
    return Atom_fromBytes(buffer, (size_t) length);
}

size_t Atom_length(Atom atom) {
    assert(atom);
    Atom_assertValidInstance(atom);
    struct Atom_Node *node = ((struct Atom_Node *) atom) - 1;
    return node->length;
}

bool Atom_equals(Atom atom, Atom other) {
    assert(atom);
    assert(other);
    Atom_assertValidInstance(atom);
    Atom_assertValidInstance(other);
    return atom == other;
}

/*
 *
 */
struct Atom_Node *Atom_Node_new(const void *const bytes, const size_t length, const uint32_t hash) {
    assert(bytes);
    assert(length < SIZE_MAX);
    struct Atom_Node *self = Option_unwrap(Alligator_malloc(length + 1));
    memcpy(self->bytes, bytes, length);
    self->hash = hash;
    self->length = length;
    self->next = NULL;
    return self;
}

uint32_t Atom_hash(const void *const bytes, const size_t length) {  /* Jenkins one at time */
    size_t i = 0;
    uint32_t hash = 0;
    const uint8_t *key = bytes;
    while (i != length) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

struct Atom_Node *Atom_put(const void *const bytes, const size_t length, const uint32_t hash) {
    assert(bytes);
    assert(length < SIZE_MAX);
    struct Atom_Node *node;

    if (!initialized) {
        atexit(Atom_onExit);
        initialized = true;
    }

    node = Atom_fetch(bytes, length, hash);
    if (NULL == node) {
        const size_t index = hash % ATOM_TABLE_SIZE;

        node = Option_unwrap(Alligator_malloc(sizeof(*node) + length + 1));
        node->next = table[index];
        node->length = length;
        node->hash = hash;
        node->bytes = node + 1;

        memcpy(node->bytes, bytes, length);
        ((char *) node->bytes)[length] = 0;
        table[index] = node;
    }

    return node;
}

struct Atom_Node *Atom_fetch(const void *const bytes, const size_t length, const uint32_t hash) {
    assert(bytes);
    assert(length < SIZE_MAX);
    const size_t index = hash % ATOM_TABLE_SIZE;

    for (struct Atom_Node *current = table[index]; NULL != current; current = current->next) {
        if (length == current->length) {
            if (0 == memcmp(bytes, current->bytes, length)) {
                return current;
            }
        }
    }

    return NULL;
}

void Atom_onExit(void) {
    struct Atom_Node *node;
    for (size_t i = 0; i < ATOM_TABLE_SIZE; i++) {
        node = table[i];
        if (NULL != node) {
            for (struct Atom_Node *prev = node; NULL != node; prev = node) {
                node = node->next;
                Alligator_free(prev);
            }
        }
        table[i] = NULL;
    }
}

void Atom_assertValidInstance(Atom atom) {
    assert(atom);
    (void) atom;
#ifndef NDEBUG
    struct Atom_Node *node = ((struct Atom_Node *) atom) - 1;
    assert(NULL != Atom_fetch(node->bytes, node->length, node->hash));
#endif
}
