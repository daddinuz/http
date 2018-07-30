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

#include <http.h>

#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define Http_MaybeText_unwrap(self) \
    __Http_MaybeText_unwrap(__FILE__, __LINE__, (self))

typedef struct __Http_MaybeText {
    Text __text;
} Http_MaybeText;

extern Http_MaybeText Http_MaybeText_new(Text text)
__attribute__((__warn_unused_result__));

extern Text __Http_MaybeText_unwrap(const char *file, int line, Http_MaybeText self)
__attribute__((__warn_unused_result__, __nonnull__));

extern bool Http_MaybeText_isPresent(Http_MaybeText self)
__attribute__((__warn_unused_result__, __nonnull__));

#ifdef __cplusplus
}
#endif
