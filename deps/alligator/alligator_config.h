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

/**
* Underlying allocator configuration.
*
* Update this file is in order to change at compile time the allocator that alligator is going to use.
* Just define the macros below to what you want to use and include the proper files.
*
* WARNING:
*  The macros below are intended for internal use only, DO NOT INCLUDE THIS FILE directly in your code.
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) || (defined(__cplusplus) && __cplusplus >= 201103L)

#include <stdalign.h>

#define __Alligator_aligned_alloc(alignment, size) \
    aligned_alloc((alignment), (size))

#endif

#define __Alligator_malloc(size) \
    malloc((size))

#define __Alligator_calloc(numberOfMembers, memberSize) \
    calloc((numberOfMembers), (memberSize))

#define __Alligator_realloc(ptr, newSize) \
    realloc((ptr), (newSize))

#define __Alligator_free(ptr) \
    free((ptr))

#ifdef __cplusplus
}
#endif
