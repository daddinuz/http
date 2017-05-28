/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017 
 * email:  daddinuz@gmal.com
 */

#include "http_dict.h"
#include "http_string.h"

#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HttpRequest {
    const HttpString method;        /* HTTP method to use. */
    const HttpString url;           /* URL to send. */
    const HttpDictEntry *headers;   /* Headers to be attached to the request. */
    const HttpString body;          /* Body to be attached to the request. */
} HttpRequest;

/**
 * Construct a new HttpRequest object.
 * This function just puts together all the pieces needed to construct
 * an HttpRequest object without performing any operation on them, so
 * it expects `method`, `url`, `body` to be HttpString(s) allocated using `http_string_new`
 *
 * @param method    Http method
 * @param url       URL to call
 * @param headers   Http headers
 * @param body      Http body
 * @return `HttpRequest *` The newly created http request
 */
extern HttpRequest *http_request_bake(
        HttpString method,
        HttpString url,
        const HttpDictEntry *headers,
        HttpString body
);

/**
 * Construct a new HttpRequest object.
 * This function is a shortcut in order to properly construct an HttpRequest object.
 * It will call `http_string_new` function on `method`, `url`, `body` parameters
 * and then will call `http_request_bake` in order to construct the request.
 *
 * @param method    Http method
 * @param url       URL to call
 * @param headers   Http headers
 * @param body      Http body
 * @return `HttpRequest *` The newly created http request
 */
extern HttpRequest *http_request_new(
        const char *method,
        const char *url,
        const HttpDictEntry *headers,
        const char *body
);

/**
 * Delete an HttpRequest object freeing its memory.
 *
 * @param self  The HttpRequest object to delete
 */
extern void http_request_delete(HttpRequest *self);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_REQUEST_H__ */
