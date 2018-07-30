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
#include <option/option.h>

#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

#define ALLIGATOR_VERSION_MAJOR       0
#define ALLIGATOR_VERSION_MINOR       24
#define ALLIGATOR_VERSION_PATCH       0
#define ALLIGATOR_VERSION_SUFFIX      ""
#define ALLIGATOR_VERSION_IS_RELEASE  0
#define ALLIGATOR_VERSION_HEX         0x002400

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) || (defined(__cplusplus) && __cplusplus >= 201103L)

extern Option Alligator_aligned_alloc(size_t alignment, size_t size)
__attribute__((__warn_unused_result__));

#endif

extern Option Alligator_malloc(size_t size)
__attribute__((__warn_unused_result__));

extern Option Alligator_calloc(size_t numberOfMembers, size_t memberSize)
__attribute__((__warn_unused_result__));

extern Option Alligator_realloc(void *ptr, size_t newSize)
__attribute__((__warn_unused_result__));

extern void Alligator_free(void *ptr);

#ifdef __cplusplus
}
#endif
