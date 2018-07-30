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

#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum HttpMethod {
    HTTP_METHOD_DELETE,
    HTTP_METHOD_GET,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_POST,
    HTTP_METHOD_PUT,
    HTTP_METHOD_CONNECT,
    HTTP_METHOD_OPTIONS,
    HTTP_METHOD_TRACE,
    HTTP_METHOD_COPY,
    HTTP_METHOD_LOCK,
    HTTP_METHOD_MOVE,
    HTTP_METHOD_SEARCH,
    HTTP_METHOD_UNLOCK,
    HTTP_METHOD_BIND,
    HTTP_METHOD_REBIND,
    HTTP_METHOD_UNBIND,
    HTTP_METHOD_REPORT,
    HTTP_METHOD_CHECKOUT,
    HTTP_METHOD_MERGE,
    HTTP_METHOD_NOTIFY,
    HTTP_METHOD_SUBSCRIBE,
    HTTP_METHOD_UNSUBSCRIBE,
    HTTP_METHOD_PATCH,
    HTTP_METHOD_PURGE,
    HTTP_METHOD_LINK,
    HTTP_METHOD_UNLINK
};

/**
 * Returns the string representation of the http method.
 *
 * @param method The http method.
 * @return The string representation of the http method.
 */
extern const char *
HttpMethod_explain(enum HttpMethod method)
__attribute__((__warn_unused_result__));

#ifdef __cplusplus
}
#endif
