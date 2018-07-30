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

struct HttpResponse;

extern const struct HttpRequest *
HttpResponse_getRequest(const struct HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern Atom
HttpResponse_getUrl(const struct HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern TextView
HttpResponse_getHeaders(const struct HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern TextView
HttpResponse_getBody(const struct HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern enum HttpStatus
HttpResponse_getStatus(const struct HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern void
HttpResponse_delete(const struct HttpResponse *self);

/*
 * Builder
 */

struct HttpResponseBuilder;

extern struct HttpResponseBuilder *
HttpResponseBuilder_new(const struct HttpRequest **ref)
__attribute__((__warn_unused_result__, __nonnull__));

extern enum HttpStatus
HttpResponseBuilder_setStatus(struct HttpResponseBuilder *self, enum HttpStatus status)
__attribute__((__nonnull__));

extern Atom
HttpResponseBuilder_setUrl(struct HttpResponseBuilder *self, Atom url)
__attribute__((__nonnull__));

extern Http_MaybeText
HttpResponseBuilder_setHeaders(struct HttpResponseBuilder *self, Text *ref)
__attribute__((__nonnull__(1)));

extern Http_MaybeText
HttpResponseBuilder_emplaceHeaders(struct HttpResponseBuilder *self, const char *format, ...)
__attribute__((__nonnull__(1, 2), __format__(printf, 2, 3)));

extern Http_MaybeText
HttpResponseBuilder_setBody(struct HttpResponseBuilder *self, Text *ref)
__attribute__((__nonnull__(1)));

extern Http_MaybeText
HttpResponseBuilder_emplaceBody(struct HttpResponseBuilder *self, const char *format, ...)
__attribute__((__nonnull__(1, 2), __format__(printf, 2, 3)));

extern const struct HttpResponse *
HttpResponseBuilder_build(struct HttpResponseBuilder **ref)
__attribute__((__warn_unused_result__, __nonnull__));

extern void
HttpResponseBuilder_delete(struct HttpResponseBuilder *self);

#ifdef __cplusplus
}
#endif
