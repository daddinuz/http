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

#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

#define ERROR_VERSION_MAJOR       0
#define ERROR_VERSION_MINOR       2
#define ERROR_VERSION_PATCH       0
#define ERROR_VERSION_SUFFIX      ""
#define ERROR_VERSION_IS_RELEASE  0
#define ERROR_VERSION_HEX         0x000200

/**
 * Represents errors that may occur at runtime.
 * Every error instance must be a singleton, in order to check if two errors are equal a simple comparison
 * between pointers can be done.
 *
 * @attention
 *  This type must be treated as opaque therefore its members should never be accessed directly.
 */
typedef struct __Error {
    const char *__message;
} const *Error;

/**
 * An helper macro used for type hinting, useful when writing interfaces.
 * By convention the annotations are the errors that may be returned.
 */
#define ErrorOf(...) \
    Error

/**
 * Helper macro to create new singleton errors.
 * This macro should be used only to define new global errors, and Errors defined with this macro must be declared const:
 *
 * @code
 * const Error OutOfMemoryError = Error_new("Out of memory");
 * @endcode
 */
#define Error_new(xMessage) \
     ((Error) &((const struct __Error) {.__message=(xMessage)}))

/**
 * Gets the error message explanation.
 *
 * @param self The error instance <b>must not be NULL</b>.
 * @return The error message.
 */
extern const char *
Error_explain(Error self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * The Ok Error instance to notify a successful execution.
 */
extern const Error Ok;

/**
 * Some error instances
 */
extern const Error OutOfMemory;

#ifdef __cplusplus
}
#endif
