/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017 
 * email:  daddinuz@gmal.com
 */

#include <stddef.h>
#include "http_request.h"

#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HttpResponse {
    HttpRequest *const request;   /* Related HTTP request */
    const int status_code;        /* HTTP status response code. */
    const HttpString url;         /* URL where has been sent. */
    const HttpString raw_headers; /* Response raw headers. */
    const HttpString raw_body;    /* Response raw_body. */
    const size_t headers_length;  /* Headers length */
    const size_t body_length;     /* Body length */
} HttpResponse;

/**
 * Construct a new HttpResponse object.
 * This function just puts together all the pieces needed to construct
 * an HttpResponse object without performing any operation on them, so
 * it expects `url`, `raw_headers`, `raw_body` to be HttpString(s) allocated using `http_string_new`
 *
 * @param request           The associated http request
 * @param status_code       The response http status code
 * @param url               The effective URL called
 * @param raw_headers       The response raw http headers
 * @param headers_length    The size of the headers
 * @param raw_body          The response raw http body
 * @param body_length       The size of the body
 * @return `HttpResponse *` The newly created http response
 */
extern HttpResponse *http_response_bake(
        HttpRequest *request,
        int status_code,
        HttpString url,
        HttpString raw_headers,
        size_t headers_length,
        HttpString raw_body,
        size_t body_length
);

/**
 * Construct a new HttpResponse object.
 * This function is a shortcut in order to properly construct an HttpResponse object.
 * It will call `http_string_new` function on `url`, `raw_headers`, `raw_body` parameters
 * and calculate the respective lengths then will call `http_response_bake` in order to construct the response.
 *
 * @param request       The associated http request
 * @param status_code   The response http status code
 * @param url           The effective URL called 
 * @param raw_headers   The response raw http headers
 * @param raw_body      The response raw http body
 * @return `HttpResponse *` The newly created http response
 */
extern HttpResponse *http_response_new(
        HttpRequest *request,
        int status_code,
        const char *url,
        const char *raw_headers,
        const char *raw_body
);

/**
 * Delete an HttpResponse object freeing its memory.
 * NOTE:
 *   This function will not delete the attached request.
 *
 * @param self  The HttpResponse object to delete
 */
extern void http_response_delete(HttpResponse *self);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_RESPONSE_H__ */
