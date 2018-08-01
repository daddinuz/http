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

#include <stddef.h>
#include <stdbool.h>

#include <atom/atom.h>
#include <text/text.h>
#include <error/error.h>

#include <http_error.h>
#include <http_fire_result.h>
#include <http_maybe_text.h>
#include <http_method.h>
#include <http_request.h>
#include <http_response.h>
#include <http_status.h>

#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initializes http module.
 *
 * @attention must be called at least once in every program that uses the http module, before firing any request.
 */
extern void Http_initialize(void);

/**
 * Terminates the http module freeing memory.
 * 
 * @attention must be called at least once in every program that uses the http module; After calling this functions 
 * it's not allowed to fire a request without calling Http_initialize() before.
 */
extern void Http_terminate(void);

/**
 * Gets the singleton instance of a readonly  empty string.
 */
extern TextView Http_getEmptyString(void)
__attribute__((__warn_unused_result__));

#ifdef __cplusplus
}
#endif
