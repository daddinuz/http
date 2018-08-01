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

struct HttpRequest;

/**
 * Returns the http method associated to this request.
 *
 * @attention self must not be NULL.
 */
extern enum HttpMethod
HttpRequest_getMethod(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the url associated to this request.
 *
 * @attention self must not be NULL.
 */
extern Atom
HttpRequest_getUrl(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the headers associated to this request.
 * Note: The current request is the owner of these headers, therefore they must be considered read-only.
 *
 * @attention self must not be NULL.
 */
extern TextView
HttpRequest_getHeaders(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the body associated to this request.
 * Note: The current request is the owner of the body, therefore it must be considered read-only.
 *
 * @attention self must not be NULL.
 */
extern TextView
HttpRequest_getBody(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the timeout for this request.
 *
 * @attention self must not be NULL.
 */
extern size_t
HttpRequest_getTimeout(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns true if follow location is enabled for this request else false.
 *
 * @attention self must not be NULL.
 */
extern bool
HttpRequest_getFollowLocation(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns true if peer verification is enabled for this request else false.
 *
 * @attention self must not be NULL.
 */
extern bool
HttpRequest_getPeerVerification(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns true if host verification is enabled for this request else false.
 *
 * @attention self must not be NULL.
 */
extern bool
HttpRequest_getHostVerification(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO check
 *
 * Sends the http request to the server waiting for response.
 *
 * @attention self must not be NULL.
 * @attention on success this function moves the ownership of the request to the resulting response
 * invalidating any previous reference to the request, on error the reference to the request is left untouched.
 */
extern Http_FireResult
HttpRequest_fire(const struct HttpRequest **ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this request freeing memory.
 * Note: If self is NULL no action will be performed.
 */
extern void
HttpRequest_delete(const struct HttpRequest *self);

/*
 * Builder
 */

struct HttpRequestBuilder;

/**
 * Creates a new request builder.
 *
 * @attention url must not be NULL.
 * @attention the lifetime of url must be greater of the builder instance or the built request (if any).
 */
extern struct HttpRequestBuilder *
HttpRequestBuilder_new(enum HttpMethod method, Atom url)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Sets the method for the request stored into this builder.
 *
 * @attention self must not be NULL.
 *
 * @return The previous http method stored into this builder.
 */
extern enum HttpMethod
HttpRequestBuilder_setMethod(struct HttpRequestBuilder *self, enum HttpMethod method)
__attribute__((__nonnull__));

/**
 * Sets the url for the request stored into this builder.
 * 
 * @attention self must not be NULL.
 * @attention url must not be NULL.
 * @attention the lifetime of url must be greater of the builder instance or the built request (if any).
 *
 * @return The previous url stored into this builder.
 */
extern Atom
HttpRequestBuilder_setUrl(struct HttpRequestBuilder *self, Atom url)
__attribute__((__nonnull__));

/**
 * Sets the headers for the request stored into this builder.
 *
 * @attention self must not be NULL.
 * @attention the user is responsible to free the replaced headers (if any).
 * @attention this function moves the ownership of the headers to this builder invalidating every previous reference.
 *
 * @return The previous headers stored into this builder.
 */
extern Http_MaybeText
HttpRequestBuilder_setHeaders(struct HttpRequestBuilder *self, Text *ref)
__attribute__((__nonnull__(1)));

/**
 * Construct in place and replace the headers for the request stored into this builder.
 * 
 * @attention self must not be NULL.
 * @attention format must not be NULL.
 * @attention the user is responsible to free the replaced headers (if any).
 * 
 * @return The previous headers stored into this builder.
 */
extern Http_MaybeText
HttpRequestBuilder_emplaceHeaders(struct HttpRequestBuilder *self, const char *format, ...)
__attribute__((__nonnull__(1, 2), __format__(printf, 2, 3)));

/**
 * Sets the body for the request stored into this builder.
 *
 * @attention self must not be NULL.
 * @attention the user is responsible to free the replaced body (if any).
 * @attention this function moves the ownership of the body to this builder invalidating every previous reference.
 *
 * @return The previous body stored into this builder.
 */
extern Http_MaybeText
HttpRequestBuilder_setBody(struct HttpRequestBuilder *self, Text *ref)
__attribute__((__nonnull__(1)));

/**
 * Construct in place and replace the body for the request stored into this builder.
 * 
 * @attention self must not be NULL.
 * @attention format must not be NULL.
 * @attention the user is responsible to free the replaced body (if any).
 * 
 * @return The previous body stored into this builder.
 */
extern Http_MaybeText
HttpRequestBuilder_emplaceBody(struct HttpRequestBuilder *self, const char *format, ...)
__attribute__((__nonnull__(1, 2), __format__(printf, 2, 3)));

/**
 * Sets the timeout for the request stored into this builder.
 *
 * @attention self must not be NULL.
 *
 * @return The previous timeout stored into this builder.
 */
extern size_t
HttpRequestBuilder_setTimeout(struct HttpRequestBuilder *self, size_t timeout)
__attribute__((__nonnull__));

/**
 * Enables or disables follow location for the request stored into this builder.
 *
 * @attention self must not be NULL.
 *
 * @return The previous value stored into this builder.
 */
extern bool
HttpRequestBuilder_setFollowLocation(struct HttpRequestBuilder *self, bool enable)
__attribute__((__nonnull__));

/**
 * Enables or disables peer verification for the request stored into this builder.
 *
 * @attention self must not be NULL.
 *
 * @return The previous value stored into this builder.
 */
extern bool
HttpRequestBuilder_setPeerVerification(struct HttpRequestBuilder *self, bool enable)
__attribute__((__nonnull__));

/**
 * Enables or disables host verification for the request stored into this builder.
 *
 * @attention self must not be NULL.
 *
 * @return The previous value stored into this builder.
 */
extern bool
HttpRequestBuilder_setHostVerification(struct HttpRequestBuilder *self, bool enable)
__attribute__((__nonnull__));

/**
 * Constructs the http request and deletes this builder freeing memory.
 *
 * @attention ref must not be NULL.
 * @attention *ref must not be NULL.
 * @attention this functions takes the ownership of this builder invalidating every previous reference.
 */
extern const struct HttpRequest *
HttpRequestBuilder_build(struct HttpRequestBuilder **ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this builder freeing memory.
 * If self is NULL no action will be performed.
 */
extern void
HttpRequestBuilder_delete(struct HttpRequestBuilder *self);

#ifdef __cplusplus
}
#endif
