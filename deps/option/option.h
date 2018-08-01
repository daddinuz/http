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

#include <stdbool.h>

#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

#define OPTION_VERSION_MAJOR       0
#define OPTION_VERSION_MINOR       22
#define OPTION_VERSION_PATCH       0
#define OPTION_VERSION_SUFFIX      ""
#define OPTION_VERSION_IS_RELEASE  0
#define OPTION_VERSION_HEX         0x002200

/**
 * Option represents encapsulation of an optional value; it is used as the return type of functions which may or may
 * not return a meaningful value when they are applied.
 *
 * @attention
 *  This type must be treated as opaque therefore its members should never be accessed directly.
 */
typedef struct __Option {
    void *__value;
} Option;

/**
 * An helper macro used for type hinting, useful when writing interfaces.
 * By convention the annotated type is the wrapped value type.
 */
#define OptionOf(xType) \
    Option

/**
 * The None Option instance used instead of NULL to represent the absence of a value.
 */
extern const Option None;

/**
 * Creates an Option wrapping a value.
 *
 * @param value The wrapped value <b>must not be NULL</b>.
 * @return A new Option instance wrapping value.
 */
extern Option Option_some(void *value)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Tests if Option is None
 *
 * @param self The Option instance.
 * @return false if Option is None else true.
 */
extern bool Option_isSome(Option self)
__attribute__((__warn_unused_result__));

/**
 * Tests if Option is None
 *
 * @param self The Option instance.
 * @return true if Option is None else false.
 */
extern bool Option_isNone(Option self)
__attribute__((__warn_unused_result__));

/**
 * Unwraps an Option, yielding its wrapped value if it's not None.
 * Aborts execution if Option is None.
 *
 * @attention
 *  This function should never be used directly, used the exported macro instead.
 *
 * @param file The file name.
 * @param line The line number.
 * @param self The Option instance.
 * @param format The custom panic message.
 * @param ... The format params.
 * @return The unwrapped value or terminates the execution.
 */
extern void *__Option_expect(const char *file, int line, Option self, const char *format, ...)
__attribute__((__warn_unused_result__, __nonnull__, __format__(__printf__, 4, 5)));

/**
 * @see __Option_expect(const char *file, int line, Option self, const char *format, ...)
 */
#define Option_expect(xSelf, ...) \
    __Option_expect(__FILE__, __LINE__, (xSelf), __VA_ARGS__)

/**
 * Unwraps an Option, yielding its wrapped value if it's not None.
 * Aborts execution if Option is None.
 *
 * @attention
 *  This function should never be used directly, used the exported macro instead.
 *
 * @param file The file name.
 * @param line The line number.
 * @param self The Option instance.
 * @return The unwrapped value or terminates the execution.
 */
extern void *__Option_unwrap(const char *file, int line, Option self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * @see __Option_unwrap(const char *file, int line, Option self)
 */
#define Option_unwrap(xSelf) \
    __Option_unwrap(__FILE__, __LINE__, (xSelf))

#ifdef __cplusplus
}
#endif
