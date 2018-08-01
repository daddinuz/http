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
#include <alligator/alligator.h>

struct HttpResponse {
    const struct HttpRequest *request;
    Atom url;
    Text headers;
    Text body;
    enum HttpStatus status;
};

const struct HttpRequest *HttpResponse_getRequest(const struct HttpResponse *self) {
    assert(self);
    return self->request;
}

Atom HttpResponse_getUrl(const struct HttpResponse *self) {
    assert(self);
    return self->url;
}

TextView HttpResponse_getHeaders(const struct HttpResponse *self) {
    assert(self);
    return NULL == self->headers ? Http_getEmptyString() : self->headers;
}

TextView HttpResponse_getBody(const struct HttpResponse *self) {
    assert(self);
    return NULL == self->body ? Http_getEmptyString() : self->body;
}

enum HttpStatus HttpResponse_getStatus(const struct HttpResponse *self) {
    assert(self);
    return self->status;
}

void HttpResponse_delete(const struct HttpResponse *self) {
    if (self) {
        HttpRequest_delete(self->request);
        Text_delete(self->body);
        Text_delete(self->headers);
        Alligator_free((void *) self);
    }
}

struct HttpResponseBuilder {
    struct HttpResponse *response;
};

struct HttpResponseBuilder *HttpResponseBuilder_new(const struct HttpRequest **ref) {
    assert(ref);
    assert(*ref);
    struct HttpResponse *response = Option_unwrap(Alligator_malloc(sizeof(*response)));
    struct HttpResponseBuilder *self = Option_unwrap(Alligator_malloc(sizeof(*self)));
    response->request = *ref;
    response->url = HttpRequest_getUrl(*ref);
    response->headers = NULL;
    response->body = NULL;
    response->status = HTTP_STATUS_OK;
    self->response = response;
    *ref = NULL;
    return self;
}

enum HttpStatus HttpResponseBuilder_setStatus(struct HttpResponseBuilder *self, enum HttpStatus status) {
    assert(self);
    const enum HttpStatus previousStatus = self->response->status;
    self->response->status = status;
    return previousStatus;
}

Atom HttpResponseBuilder_setUrl(struct HttpResponseBuilder *self, Atom url) {
    assert(self);
    Atom previousUrl = self->response->url;
    self->response->url = url;
    return previousUrl;
}

Http_MaybeText HttpResponseBuilder_setHeaders(struct HttpResponseBuilder *self, Text *ref) {
    assert(self);
    Text previousHeaders = self->response->headers;
    if (NULL != ref) {
        assert(*ref);
        self->response->headers = *ref;
        *ref = NULL;
    }
    return Http_MaybeText_new(previousHeaders);
}

Http_MaybeText HttpResponseBuilder_emplaceHeaders(struct HttpResponseBuilder *self, const char *format, ...) {
    assert(self);
    assert(format);
    va_list args;
    va_start(args, format);
    Text headers = Text_vFormat(format, args);
    va_end(args);
    return HttpResponseBuilder_setHeaders(self, &headers);
}

Http_MaybeText HttpResponseBuilder_setBody(struct HttpResponseBuilder *self, Text *ref) {
    assert(self);
    Text previousBody = self->response->body;
    if (NULL != ref) {
        assert(*ref);
        self->response->body = *ref;
        *ref = NULL;
    }
    return Http_MaybeText_new(previousBody);
}

Http_MaybeText HttpResponseBuilder_emplaceBody(struct HttpResponseBuilder *self, const char *format, ...) {
    assert(self);
    assert(format);
    va_list args;
    va_start(args, format);
    Text body = Text_vFormat(format, args);
    va_end(args);
    return HttpResponseBuilder_setBody(self, &body);
}

const struct HttpResponse *HttpResponseBuilder_build(struct HttpResponseBuilder **ref) {
    assert(ref);
    assert(*ref);
    const struct HttpResponse *response = (*ref)->response;
    Alligator_free(*ref);
    *ref = NULL;
    return response;
}

void HttpResponseBuilder_delete(struct HttpResponseBuilder *self) {
    if (self) {
        HttpResponse_delete(self->response);
        Alligator_free(self);
    }
}
