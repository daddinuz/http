/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017 
 * email:  daddinuz@gmal.com
 */

#include "http_dict.h"

#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HttpRequest {
    char *method;           /* HTTP method to use. */
    char *url;              /* URL to send. */
    HttpDictEntry *headers; /* Headers to be attached to the request. */
    char *body;             /* Body to be attached to the request. */
} HttpRequest;

extern HttpRequest http_request_create(
        const char *method,
        const char *url,
        HttpDict headers,
        const char *body
);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_REQUEST_H__ */
