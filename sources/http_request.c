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

#include <http.h>
#include <assert.h>
#include <stdlib.h>
#include <alligator/alligator.h>

struct HttpRequest {
    Atom url;
    Text headers;
    Text body;
    size_t timeout;
    bool followLocation;
    bool peerVerification;
    bool hostVerification;
    enum HttpMethod method;
};

enum HttpMethod HttpRequest_getMethod(const struct HttpRequest *self) {
    assert(self);
    return self->method;
}

Atom HttpRequest_getUrl(const struct HttpRequest *self) {
    assert(self);
    return self->url;
}

TextView HttpRequest_getHeaders(const struct HttpRequest *self) {
    assert(self);
    return NULL == self->headers ? Http_getEmptyHeaders() : self->headers;
}

TextView HttpRequest_getBody(const struct HttpRequest *self) {
    assert(self);
    return NULL == self->body ? Http_getEmptyBody() : self->body;
}

size_t HttpRequest_getTimeout(const struct HttpRequest *self) {
    assert(self);
    return self->timeout;
}

bool HttpRequest_getFollowLocation(const struct HttpRequest *self) {
    assert(self);
    return self->followLocation;
}

bool HttpRequest_getPeerVerification(const struct HttpRequest *self) {
    assert(self);
    return self->peerVerification;
}

bool HttpRequest_getHostVerification(const struct HttpRequest *self) {
    assert(self);
    return self->hostVerification;
}

void HttpRequest_delete(const struct HttpRequest *self) {
    if (self) {
        Text_delete(self->body);
        Text_delete(self->headers);
        Alligator_free((void *) self);
    }
}

struct HttpRequestBuilder {
    struct HttpRequest *request;
};

struct HttpRequestBuilder *HttpRequestBuilder_new(enum HttpMethod method, Atom url) {
    assert(url);
    struct HttpRequest *request = Option_unwrap(Alligator_malloc(sizeof(*request)));
    struct HttpRequestBuilder *self = Option_unwrap(Alligator_malloc(sizeof(*self)));
    request->url = url;
    request->headers = NULL;
    request->body = NULL;
    request->timeout = 0;
    request->followLocation = true;
    request->peerVerification = true;
    request->hostVerification = true;
    request->method = method;
    self->request = request;
    return self;
}

enum HttpMethod HttpRequestBuilder_setMethod(struct HttpRequestBuilder *self, enum HttpMethod method) {
    assert(self);
    const enum HttpMethod previousMethod = self->request->method;
    self->request->method = method;
    return previousMethod;
}

Atom HttpRequestBuilder_setUrl(struct HttpRequestBuilder *self, Atom url) {
    assert(self);
    Atom previousUrl = self->request->url;
    self->request->url = url;
    return previousUrl;
}

Http_MaybeText HttpRequestBuilder_setHeaders(struct HttpRequestBuilder *self, Text *ref) {
    assert(self);
    Text previousHeaders = self->request->headers;
    if (NULL != ref) {
        assert(*ref);
        self->request->headers = *ref;
        *ref = NULL;
    }
    return Http_MaybeText_new(previousHeaders);
}

Http_MaybeText HttpRequestBuilder_emplaceHeaders(struct HttpRequestBuilder *self, const char *format, ...) {
    assert(self);
    assert(format);
    va_list args;
    va_start(args, format);
    Text headers = Text_vFormat(format, args);
    va_end(args);
    return HttpRequestBuilder_setHeaders(self, &headers);
}

Http_MaybeText HttpRequestBuilder_setBody(struct HttpRequestBuilder *self, Text *ref) {
    assert(self);
    Text previousBody = self->request->body;
    if (NULL != ref) {
        assert(*ref);
        self->request->body = *ref;
        *ref = NULL;
    }
    return Http_MaybeText_new(previousBody);
}

Http_MaybeText HttpRequestBuilder_emplaceBody(struct HttpRequestBuilder *self, const char *format, ...) {
    assert(self);
    assert(format);
    va_list args;
    va_start(args, format);
    Text body = Text_vFormat(format, args);
    va_end(args);
    return HttpRequestBuilder_setBody(self, &body);
}

size_t HttpRequestBuilder_setTimeout(struct HttpRequestBuilder *self, size_t timeout) {
    assert(self);
    const size_t previousTimeout = self->request->timeout;
    self->request->timeout = timeout;
    return previousTimeout;
}

bool HttpRequestBuilder_setFollowLocation(struct HttpRequestBuilder *self, bool enable) {
    assert(self);
    const bool previousFollowLocation = self->request->followLocation;
    self->request->followLocation = enable;
    return previousFollowLocation;
}

bool HttpRequestBuilder_setPeerVerification(struct HttpRequestBuilder *self, bool enable) {
    assert(self);
    const bool previousPeerVerification = self->request->peerVerification;
    self->request->peerVerification = enable;
    return previousPeerVerification;
}

bool HttpRequestBuilder_setHostVerification(struct HttpRequestBuilder *self, bool enable) {
    assert(self);
    const bool previousHostVerification = self->request->hostVerification;
    self->request->hostVerification = enable;
    return previousHostVerification;
}

const struct HttpRequest *HttpRequestBuilder_build(struct HttpRequestBuilder **ref) {
    assert(ref);
    assert(*ref);
    const struct HttpRequest *request = (*ref)->request;
    Alligator_free(*ref);
    *ref = NULL;
    return request;
}

void HttpRequestBuilder_delete(struct HttpRequestBuilder *self) {
    if (self) {
        HttpRequest_delete(self->request);
        Alligator_free(self);
    }
}
