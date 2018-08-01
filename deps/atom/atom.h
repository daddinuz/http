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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>

#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

#define ATOM_VERSION_MAJOR          0
#define ATOM_VERSION_MINOR          1
#define ATOM_VERSION_PATCH          0
#define ATOM_VERSION_SUFFIX         ""
#define ATOM_VERSION_IS_RELEASE     0
#define ATOM_VERSION_HEX            0x000100

/**
 * Atoms are pointers to a unique, immutable, sequence of zero or more arbitrary bytes.
 * There is only a single occurrence of any atom, which is why it’s called an atom.
 * Two atoms are identical if they point to the same location.
 * One of the advantages of atoms is that comparing two byte sequences for equality is performed by simply comparing pointers.
 * Another advantage is that using atoms saves space because there’s only one occurrence of each sequence.
 * Atoms are often used as keys in data structures that are indexed by sequences of arbitrary bytes instead of by integers.
 */
typedef const char *Atom;

/**
 * Gets the Atom instance or creates a new one if not exists from a sequence of bytes.
 *
 * @attention bytes must not be NULL.
 * @attention length must be < SIZE_MAX.
 */
extern Atom
Atom_fromBytes(const void *bytes, size_t length)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Gets the Atom instance or creates a new one if not exists from the given literal.
 *
 * @attention literal must not be NULL.
 * @attention strlen(literal) must be < SIZE_MAX.
 */
extern Atom
Atom_fromLiteral(const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Gets the Atom instance or creates a new one if not exists from the given integer number.
 */
extern Atom
Atom_fromInteger(long long number)
__attribute__((__warn_unused_result__));

/**
 * Gets the Atom instance or creates a new one if not exists from the given floating number.
 */
extern Atom
Atom_fromFloating(long double number)
__attribute__((__warn_unused_result__));

/**
 * Gets the length of the atom.
 *
 * @attention atom must not be NULL and must be a valid Atom instance.
 *
 * @param atom The Atom instance.
 * @return The length of the atom.
 */
extern size_t
Atom_length(Atom atom)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Checks for equality.
 *
 * @attention atom must not be NULL.
 * @attention other must not be NULL.
 */
extern bool
Atom_equals(Atom atom, Atom other)
__attribute__((__warn_unused_result__, __nonnull__));

#ifdef __cplusplus
}
#endif
