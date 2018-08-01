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

#include <stdarg.h>

#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

#define PANIC_VERSION_MAJOR       0
#define PANIC_VERSION_MINOR       3
#define PANIC_VERSION_PATCH       0
#define PANIC_VERSION_SUFFIX      ""
#define PANIC_VERSION_IS_RELEASE  0
#define PANIC_VERSION_HEX         0x000300

/**
 * Type signature of the callback function to be executed on exit.
 */
typedef void (*Panic_Callback)(void);

/**
 * Registers a callback to execute before terminating.
 *
 * @param callback The callback to be executed, if NULL nothing will be executed.
 * @return The previous registered callback if any else NULL.
 */
extern Panic_Callback Panic_registerCallback(Panic_Callback callback);

/**
 * Reports the error and terminates execution.
 * @warning This function should not be called directly, use the exported macro instead.
 */
extern void __Panic_terminate(const char *file, int line, const char *format, ...)
__attribute__((__nonnull__, __format__(__printf__, 3, 4), __noreturn__));

/**
 * Like __panic but takes a variadic list.
 *
 * @see __panic(const char *file, int line, const char *format, ...)
 *
 * @warning This function should not be called directly, use the exported macro instead.
 */
extern void __Panic_vterminate(const char *file, int line, const char *format, va_list args)
__attribute__((__nonnull__, __format__(__printf__, 3, 0), __noreturn__));

/**
 * This macro acts like a wrapper over __panic function passing the right
 * call coordinates (file and line number) for a better error report.
 */
#define Panic_terminate(...) \
    __Panic_terminate(__FILE__, __LINE__, __VA_ARGS__)

#ifdef __cplusplus
}
#endif
