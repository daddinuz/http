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
#include <panic/panic.h>

static const char HTTP_METHOD_DELETE_EXPLANATION[] = "DELETE";
static const char HTTP_METHOD_GET_EXPLANATION[] = "GET";
static const char HTTP_METHOD_HEAD_EXPLANATION[] = "HEAD";
static const char HTTP_METHOD_POST_EXPLANATION[] = "POST";
static const char HTTP_METHOD_PUT_EXPLANATION[] = "PUT";
static const char HTTP_METHOD_CONNECT_EXPLANATION[] = "CONNECT";
static const char HTTP_METHOD_OPTIONS_EXPLANATION[] = "OPTIONS";
static const char HTTP_METHOD_TRACE_EXPLANATION[] = "TRACE";
static const char HTTP_METHOD_COPY_EXPLANATION[] = "COPY";
static const char HTTP_METHOD_LOCK_EXPLANATION[] = "LOCK";
static const char HTTP_METHOD_MOVE_EXPLANATION[] = "MOVE";
static const char HTTP_METHOD_SEARCH_EXPLANATION[] = "SEARCH";
static const char HTTP_METHOD_UNLOCK_EXPLANATION[] = "UNLOCK";
static const char HTTP_METHOD_BIND_EXPLANATION[] = "BIND";
static const char HTTP_METHOD_REBIND_EXPLANATION[] = "REBIND";
static const char HTTP_METHOD_UNBIND_EXPLANATION[] = "UNBIND";
static const char HTTP_METHOD_REPORT_EXPLANATION[] = "REPORT";
static const char HTTP_METHOD_CHECKOUT_EXPLANATION[] = "CHECKOUT";
static const char HTTP_METHOD_MERGE_EXPLANATION[] = "MERGE";
static const char HTTP_METHOD_NOTIFY_EXPLANATION[] = "NOTIFY";
static const char HTTP_METHOD_SUBSCRIBE_EXPLANATION[] = "SUBSCRIBE";
static const char HTTP_METHOD_UNSUBSCRIBE_EXPLANATION[] = "UNSUBSCRIBE";
static const char HTTP_METHOD_PATCH_EXPLANATION[] = "PATCH";
static const char HTTP_METHOD_PURGE_EXPLANATION[] = "PURGE";
static const char HTTP_METHOD_LINK_EXPLANATION[] = "LINK";
static const char HTTP_METHOD_UNLINK_EXPLANATION[] = "UNLINK";

const char *HttpMethod_explain(const enum HttpMethod method) {
    switch (method) {
        case HTTP_METHOD_DELETE:
            return HTTP_METHOD_DELETE_EXPLANATION;
        case HTTP_METHOD_GET:
            return HTTP_METHOD_GET_EXPLANATION;
        case HTTP_METHOD_HEAD:
            return HTTP_METHOD_HEAD_EXPLANATION;
        case HTTP_METHOD_POST:
            return HTTP_METHOD_POST_EXPLANATION;
        case HTTP_METHOD_PUT:
            return HTTP_METHOD_PUT_EXPLANATION;
        case HTTP_METHOD_CONNECT:
            return HTTP_METHOD_CONNECT_EXPLANATION;
        case HTTP_METHOD_OPTIONS:
            return HTTP_METHOD_OPTIONS_EXPLANATION;
        case HTTP_METHOD_TRACE:
            return HTTP_METHOD_TRACE_EXPLANATION;
        case HTTP_METHOD_COPY:
            return HTTP_METHOD_COPY_EXPLANATION;
        case HTTP_METHOD_LOCK:
            return HTTP_METHOD_LOCK_EXPLANATION;
        case HTTP_METHOD_MOVE:
            return HTTP_METHOD_MOVE_EXPLANATION;
        case HTTP_METHOD_SEARCH:
            return HTTP_METHOD_SEARCH_EXPLANATION;
        case HTTP_METHOD_UNLOCK:
            return HTTP_METHOD_UNLOCK_EXPLANATION;
        case HTTP_METHOD_BIND:
            return HTTP_METHOD_BIND_EXPLANATION;
        case HTTP_METHOD_REBIND:
            return HTTP_METHOD_REBIND_EXPLANATION;
        case HTTP_METHOD_UNBIND:
            return HTTP_METHOD_UNBIND_EXPLANATION;
        case HTTP_METHOD_REPORT:
            return HTTP_METHOD_REPORT_EXPLANATION;
        case HTTP_METHOD_CHECKOUT:
            return HTTP_METHOD_CHECKOUT_EXPLANATION;
        case HTTP_METHOD_MERGE:
            return HTTP_METHOD_MERGE_EXPLANATION;
        case HTTP_METHOD_NOTIFY:
            return HTTP_METHOD_NOTIFY_EXPLANATION;
        case HTTP_METHOD_SUBSCRIBE:
            return HTTP_METHOD_SUBSCRIBE_EXPLANATION;
        case HTTP_METHOD_UNSUBSCRIBE:
            return HTTP_METHOD_UNSUBSCRIBE_EXPLANATION;
        case HTTP_METHOD_PATCH:
            return HTTP_METHOD_PATCH_EXPLANATION;
        case HTTP_METHOD_PURGE:
            return HTTP_METHOD_PURGE_EXPLANATION;
        case HTTP_METHOD_LINK:
            return HTTP_METHOD_LINK_EXPLANATION;
        case HTTP_METHOD_UNLINK:
            return HTTP_METHOD_UNLINK_EXPLANATION;
        default:
            Panic_terminate("Unknown method: %d", method);
    }
}
