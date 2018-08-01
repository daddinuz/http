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

/**
 * Returns the http request that generated this response.
 * 
 * @attention self must not be NULL.
 */
extern const struct HttpRequest *
HttpResponse_getRequest(const struct HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the effective url associated to this response.
 * Note: response url may be different from request url if follow location were enabled for the request.
 *
 * @attention self must not be NULL.
 */
extern Atom
HttpResponse_getUrl(const struct HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the headers associated to this response.
 * Note: The current response is the owner of these headers, therefore they must be considered read-only.
 *
 * @attention self must not be NULL.
 */
extern TextView
HttpResponse_getHeaders(const struct HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the body associated to this response.
 * Note: The current response is the owner of the body, therefore it must be considered read-only.
 *
 * @attention self must not be NULL.
 */
extern TextView
HttpResponse_getBody(const struct HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the http status code associated to this response.
 *
 * @attention self must not be NULL.
 */
extern enum HttpStatus
HttpResponse_getStatus(const struct HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this response freeing memory.
 * Note: If self is NULL no action will be performed.
 */
extern void
HttpResponse_delete(const struct HttpResponse *self);

/*
 * Builder
 */

struct HttpResponseBuilder;

/**
 * Creates a new response builder.
 *
 * @attention ref must not be NULL.
 * @attention *ref must not be NULL.
 * @attention this function moves the ownership of the request to this builder invalidating every previous reference.
 */
extern struct HttpResponseBuilder *
HttpResponseBuilder_new(const struct HttpRequest **ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Sets the http status for the response stored into this builder.
 *
 * @attention self must not be NULL.
 *
 * @return The previous http status stored into this builder.
 */
extern enum HttpStatus
HttpResponseBuilder_setStatus(struct HttpResponseBuilder *self, enum HttpStatus status)
__attribute__((__nonnull__));

/**
 * Sets the url for the response stored into this builder.
 * 
 * @attention self must not be NULL.
 * @attention url must not be NULL.
 * @attention the lifetime of url must be greater of the builder instance or the built response (if any).
 *
 * @return The previous url stored into this builder.
 */
extern Atom
HttpResponseBuilder_setUrl(struct HttpResponseBuilder *self, Atom url)
__attribute__((__nonnull__));

/**
 * Sets the headers for the response stored into this builder.
 *
 * @attention self must not be NULL.
 * @attention the user is responsible to free the replaced headers (if any).
 * @attention this function moves the ownership of the headers to this builder invalidating every previous reference.
 *
 * @return The previous headers stored into this builder.
 */
extern Http_MaybeText
HttpResponseBuilder_setHeaders(struct HttpResponseBuilder *self, Text *ref)
__attribute__((__nonnull__(1)));

/**
 * Construct in place and replace the headers for the response stored into this builder.
 * 
 * @attention self must not be NULL.
 * @attention format must not be NULL.
 * @attention the user is responsible to free the replaced headers (if any).
 * 
 * @return The previous headers stored into this builder.
 */
extern Http_MaybeText
HttpResponseBuilder_emplaceHeaders(struct HttpResponseBuilder *self, const char *format, ...)
__attribute__((__nonnull__(1, 2), __format__(printf, 2, 3)));

/**
 * Sets the body for the response stored into this builder.
 *
 * @attention self must not be NULL.
 * @attention the user is responsible to free the replaced body (if any).
 * @attention this function moves the ownership of the body to this builder invalidating every previous reference.
 *
 * @return The previous body stored into this builder.
 */
extern Http_MaybeText
HttpResponseBuilder_setBody(struct HttpResponseBuilder *self, Text *ref)
__attribute__((__nonnull__(1)));

/**
 * Construct in place and replace the body for the response stored into this builder.
 * 
 * @attention self must not be NULL.
 * @attention format must not be NULL.
 * @attention the user is responsible to free the replaced body (if any).
 * 
 * @return The previous body stored into this builder.
 */
extern Http_MaybeText
HttpResponseBuilder_emplaceBody(struct HttpResponseBuilder *self, const char *format, ...)
__attribute__((__nonnull__(1, 2), __format__(printf, 2, 3)));

/**
 * Constructs the http response and deletes this builder freeing memory.
 *
 * @attention ref must not be NULL.
 * @attention *ref must not be NULL.
 * @attention this functions takes the ownership of this builder invalidating every previous reference.
 */
extern const struct HttpResponse *
HttpResponseBuilder_build(struct HttpResponseBuilder **ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this builder freeing memory.
 * If self is NULL no action will be performed.
 */
extern void
HttpResponseBuilder_delete(struct HttpResponseBuilder *self);

#ifdef __cplusplus
}
#endif
