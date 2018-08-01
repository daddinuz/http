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

#include "alligator.h"
#include "alligator_config.h"

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) || (defined(__cplusplus) && __cplusplus >= 201103L)

Option Alligator_aligned_alloc(size_t alignment, size_t size) {
    void *memory = __Alligator_aligned_alloc(alignment, size);
    return memory ? Option_some(memory) : None;
}

#endif

Option Alligator_malloc(const size_t size) {
    void *memory = __Alligator_malloc(size);
    return memory ? Option_some(memory) : None;
}

Option Alligator_calloc(const size_t numberOfMembers, const size_t memberSize) {
    void *memory = __Alligator_calloc(numberOfMembers, memberSize);
    return memory ? Option_some(memory) : None;
}

Option Alligator_realloc(void *ptr, size_t newSize) {
    void *memory = __Alligator_realloc(ptr, newSize);
    return memory ? Option_some(memory) : None;
}

void Alligator_free(void *ptr) {
    __Alligator_free(ptr);
}
