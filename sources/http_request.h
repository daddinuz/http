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
 * Returns the http method associated to the specified request.
 *
 * @attention self must not be NULL.
 *
 * @param self The HttpRequest instance.
 * @return The http method of the specified request.
 */
extern enum HttpMethod
HttpRequest_getMethod(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the url associated to the specified request.
 *
 * @attention self must not be NULL.
 *
 * @param self The HttpRequest instance.
 * @return The url associated to the specified request.
 */
extern Atom
HttpRequest_getUrl(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the headers associated to the request.
 *
 * @attention self must not be NULL.
 * @attention The current request is the owner of these headers, therefore they must be considered read-only.
 *
 * @param self The HttpRequest instance.
 * @return The headers associated to the specified request.
 */
extern TextView
HttpRequest_getHeaders(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the body associated to the request.
 *
 * @attention self must not be NULL.
 * @attention The current request is the owner of the body, therefore it must be considered read-only.
 *
 * @param self The HttpRequest instance.
 * @return The body associated to the specified request.
 */
extern TextView
HttpRequest_getBody(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the timeout associated to the specified request.
 *
 * @attention self must not be NULL.
 *
 * @param self The HttpRequest instance.
 * @return The timeout associated to the specified request.
 */
extern size_t
HttpRequest_getTimeout(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns true if follow location is enabled for the specified request else false.
 *
 * @attention self must not be NULL.
 *
 * @param self The HttpRequest instance
 * @return true if follow location is enabled for the specified request else false.
 */
extern bool
HttpRequest_getFollowLocation(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns true if peer verification is enabled for the specified request else false.
 *
 * @attention self must not be NULL.
 *
 * @param self The HttpRequest instance.
 * @return true if peer verification is enabled for the specified request else false.
 */
extern bool
HttpRequest_getPeerVerification(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns true if host verification is enabled for the specified request else false.
 *
 * @attention self must not be NULL.
 *
 * @param self The HttpRequest instance.
 * @return true if host verification is enabled for the specified request else false.
 */
extern bool
HttpRequest_getHostVerification(const struct HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Performs the http request returning the server response.
 *
 * @attention self must not be NULL.
 * @attention On success this function moves the ownership of the request to the resulting response invalidating every references.
 *
 * @param ref The reference to the request instance.
 * @return
 * - Ok => Wraps the http response, *ref has been invalidated.
 * - NetworkingError => There were something wrong with the connection, *ref has not been invalidated.
 */
extern Http_FireResult
HttpRequest_fire(const struct HttpRequest **ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of HttpRequest.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
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
 * @attention the lifetime of url must be greater of the builder instance or the built request.
 * 
 * @param method The http method for the request.
 * @param url The url for the request.
 * @return A new HttpRequestBuilder instance.
 */
extern struct HttpRequestBuilder *
HttpRequestBuilder_new(enum HttpMethod method, Atom url)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Sets the method for the request.
 *
 * @attention self must not be NULL.
 *
 * @param self The request builder instance.
 * @param method The http method for the request.
 * @return The replaced method.
 */
extern enum HttpMethod
HttpRequestBuilder_setMethod(struct HttpRequestBuilder *self, enum HttpMethod method)
__attribute__((__nonnull__));

/**
 * Sets the url for the request.
 * 
 * @attention self must not be NULL.
 * @attention url must not be NULL.
 * @attention the lifetime of url must be greater of the builder instance or the built request if any.
 *
 * @param self The request builder instance.
 * @param url Self explaining.
 * @return The replaced url.
 */
extern Atom
HttpRequestBuilder_setUrl(struct HttpRequestBuilder *self, Atom url)
__attribute__((__nonnull__));

/**
 * Sets the headers for the request.
 *
 * @attention self must not be NULL.
 * @attention the user is responsible to free the replaced headers if any.
 * @attention moves the ownership of the headers to the builder instance invalidating external references.
 *
 * @param self The request builder instance.
 * @param ref The reference to the headers instance.
 * @return The replaced headers.
 */
extern Http_MaybeText
HttpRequestBuilder_setHeaders(struct HttpRequestBuilder *self, Text *ref)
__attribute__((__nonnull__(1)));

/**
 * TODO docs
 * 
 * @param self 
 * @param format 
 * @param ... 
 * @return 
 */
extern Http_MaybeText
HttpRequestBuilder_emplaceHeaders(struct HttpRequestBuilder *self, const char *format, ...)
__attribute__((__nonnull__(1, 2), __format__(printf, 2, 3)));

/**
 * Sets the body for the request.
 *
 * @attention self must not be NULL.
 * @attention the user is responsible to free the replaced body if any.
 * @attention moves the ownership of the body to the builder instance invalidating external references.
 *
 * @param self The request builder instance.
 * @param ref The reference to the body instance.
 * @return The replaced body.
 */
extern Http_MaybeText
HttpRequestBuilder_setBody(struct HttpRequestBuilder *self, Text *ref)
__attribute__((__nonnull__(1)));

/**
 * TODO docs
 * 
 * @param self 
 * @param format 
 * @param ... 
 * @return 
 */
extern Http_MaybeText
HttpRequestBuilder_emplaceBody(struct HttpRequestBuilder *self, const char *format, ...)
__attribute__((__nonnull__(1, 2), __format__(printf, 2, 3)));

/**
 * Sets the timeout for the request.
 *
 * @attention self must not be NULL.
 *
 * @param self The request builder instance.
 * @param timeout The specified timeout.
 * @return The replaced value for timeout.
 */
extern size_t
HttpRequestBuilder_setTimeout(struct HttpRequestBuilder *self, size_t timeout)
__attribute__((__nonnull__));

/**
 * Enables or disables follow location for the request.
 *
 * @attention self must not be NULL.
 *
 * @param self The request builder instance.
 * @param enable Self explaining.
 * @return The previous value for follow location.
 */
extern bool
HttpRequestBuilder_setFollowLocation(struct HttpRequestBuilder *self, bool enable)
__attribute__((__nonnull__));

/**
 * Enables or disables peer verification for the request.
 *
 * @attention self must not be NULL.
 *
 * @param self The request builder instance.
 * @param enable Self explaining.
 * @return The previous value for peer verification.
 */
extern bool
HttpRequestBuilder_setPeerVerification(struct HttpRequestBuilder *self, bool enable)
__attribute__((__nonnull__));

/**
 * Enables or disables host verification for the request.
 *
 * @attention self must not be NULL.
 *
 * @param self The request builder instance.
 * @param enable Self explaining.
 * @return The previous value for host verification.
 */
extern bool
HttpRequestBuilder_setHostVerification(struct HttpRequestBuilder *self, bool enable)
__attribute__((__nonnull__));

/**
 * Constructs the http request.
 *
 * @attention ref must not be NULL.
 * @attention *ref must not be NULL.
 * @attention on success takes the ownership of the request builder invalidating its external references.
 *
 * @param ref The reference to the request builder instance.
 * @return The http request instance.
 */
extern const struct HttpRequest *
HttpRequestBuilder_build(struct HttpRequestBuilder **ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of HttpRequestBuilder.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
HttpRequestBuilder_delete(struct HttpRequestBuilder *self);

#ifdef __cplusplus
}
#endif
