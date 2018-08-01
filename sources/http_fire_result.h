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

/**
 * Unwraps the http response.
 * @attention Terminates execution if the result is not wrapping an http response.
 */
#define Http_FireResult_unwrap(self) \
    __Http_FireResult_unwrap(__FILE__, __LINE__, (self))

/**
 * Unwraps the error.
 * @attention Terminates execution if the result is wrapping an http response.
 */
#define Http_FireResult_unwrapError(self) \
    __Http_FireResult_unwrapError(__FILE__, __LINE__, (self))

/**
 * Either type: Either(Error, struct HttpResponse *)
 */
typedef struct __Http_FireResult {
    union {
        const struct HttpResponse *__response;
        const Error __error;
    };
    const bool __isOk;
} Http_FireResult;

/**
 * Constructs a fire result wrapping the response from the server.
 *
 * @attention response must not be NULL.
 */
extern Http_FireResult Http_FireResult_ok(const struct HttpResponse *response)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Constructs a fire result wrapping the error.
 *
 * @attention error must not be NULL.
 */
extern Http_FireResult Http_FireResult_error(Error error)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * NOTE: Do NOT use this function directly, @see Http_FireResult_unwrap.
 *
 * Unwraps the http response.
 * @attention Terminates execution if the result is not Ok.
 */
extern const struct HttpResponse *__Http_FireResult_unwrap(const char *file, int line, Http_FireResult self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * NOTE: Do NOT use this function directly, @see Http_FireResult_unwrapError.
 *
 * Unwraps the error.
 * @attention Terminates execution if the result is Ok.
 */
extern Error __Http_FireResult_unwrapError(const char *file, int line, Http_FireResult self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * @return true if the result wraps an http response else false
 */
extern bool Http_FireResult_isOk(Http_FireResult self)
__attribute__((__warn_unused_result__));

/**
 * @return true if the result wraps an error else false
 */
extern bool Http_FireResult_isError(Http_FireResult self)
__attribute__((__warn_unused_result__));

#ifdef __cplusplus
}
#endif
