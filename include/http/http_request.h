/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017 
 * email:  daddinuz@gmail.com
 */

#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include "http_dict.h"
#include "http_string.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Structure holding an Http Request
 */
typedef struct HttpRequest {
    HttpString method;    /* HTTP method to use. */
    HttpString url;       /* URL to send. */
    HttpDict *headers;    /* Headers to be attached to the request. */
    HttpString body;      /* Body to be attached to the request. */
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
extern const HttpRequest *http_request_new(
        HttpString method,
        HttpString url,
        HttpDict *headers,
        HttpString body
);

/**
 * Delete an HttpRequest object freeing its memory.
 *
 * @param self  The HttpRequest object to delete
 */
extern void http_request_delete(const HttpRequest *self);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_REQUEST_H__ */
