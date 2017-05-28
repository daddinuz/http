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

extern HttpRequest *http_request_new(
        const HttpString method,
        const HttpString url,
        const HttpDictEntry *headers,
        const HttpString body
);

extern void http_request_delete(HttpRequest **ref);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_REQUEST_H__ */
