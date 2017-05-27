/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017 
 * email:  daddinuz@gmal.com
 */

#ifndef __HTTP_STATUS_H__
#define __HTTP_STATUS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __HttpStatus {
    const int CONTINUE;
    const int SWITCHING_PROTOCOLS;
    const int OK;
    const int CREATED;
    const int ACCEPTED;
    const int NON_AUTHORITATIVE_INFORMATION;
    const int NO_CONTENT;
    const int RESET_CONTENT;
    const int PARTIAL_CONTENT;
    const int MULTIPLE_CHOICES;
    const int MOVED_PERMANENTLY;
    const int FOUND;
    const int SEE_OTHER;
    const int NOT_MODIFIED;
    const int USE_PROXY;
    const int TEMPORARY_REDIRECT;
    const int BAD_REQUEST;
    const int UNAUTHORIZED;
    const int PAYMENT_REQUIRED;
    const int FORBIDDEN;
    const int NOT_FOUND;
    const int METHOD_NOT_ALLOWED;
    const int NOT_ACCEPTABLE;
    const int PROXY_AUTHENTICATION_REQUIRED;
    const int REQUEST_TIMEOUT;
    const int CONFLICT;
    const int GONE;
    const int LENGTH_REQUIRED;
    const int PRECONDITION_FAILED;
    const int REQUEST_ENTITY_TOO_LARGE;
    const int REQUEST_URI_TOO_LONG;
    const int UNSUPPORTED_MEDIA_TYPE;
    const int REQUESTED_RANGE_NOT_SATISFIABLE;
    const int EXPECTATION_FAILED;
    const int UNPROCESSABLE_ENTITY;
    const int TOO_MANY_REQUESTS;
    const int INTERNAL_SERVER_ERROR;
    const int NOT_IMPLEMENTED;
    const int BAD_GATEWAY;
    const int SERVICE_UNAVAILABLE;
    const int GATEWAY_TIMEOUT;
    const int VERSION_NOT_SUPPORTED;
} __HttpStatus;

static const __HttpStatus HttpStatus = {
        .CONTINUE = 100,
        .SWITCHING_PROTOCOLS = 101,
        .OK = 200,
        .CREATED = 201,
        .ACCEPTED = 202,
        .NON_AUTHORITATIVE_INFORMATION = 203,
        .NO_CONTENT = 204,
        .RESET_CONTENT = 205,
        .PARTIAL_CONTENT = 206,
        .MULTIPLE_CHOICES = 300,
        .MOVED_PERMANENTLY = 301,
        .FOUND = 302,
        .SEE_OTHER = 303,
        .NOT_MODIFIED = 304,
        .USE_PROXY = 305,
        .TEMPORARY_REDIRECT = 307,
        .BAD_REQUEST = 400,
        .UNAUTHORIZED = 401,
        .PAYMENT_REQUIRED = 402,
        .FORBIDDEN = 403,
        .NOT_FOUND = 404,
        .METHOD_NOT_ALLOWED = 405,
        .NOT_ACCEPTABLE = 406,
        .PROXY_AUTHENTICATION_REQUIRED = 407,
        .REQUEST_TIMEOUT = 408,
        .CONFLICT = 409,
        .GONE = 410,
        .LENGTH_REQUIRED = 411,
        .PRECONDITION_FAILED = 412,
        .REQUEST_ENTITY_TOO_LARGE = 413,
        .REQUEST_URI_TOO_LONG = 414,
        .UNSUPPORTED_MEDIA_TYPE = 415,
        .REQUESTED_RANGE_NOT_SATISFIABLE = 416,
        .EXPECTATION_FAILED = 417,
        .UNPROCESSABLE_ENTITY = 422,
        .TOO_MANY_REQUESTS = 429,
        .INTERNAL_SERVER_ERROR = 500,
        .NOT_IMPLEMENTED = 501,
        .BAD_GATEWAY = 502,
        .SERVICE_UNAVAILABLE = 503,
        .GATEWAY_TIMEOUT = 504,
        .VERSION_NOT_SUPPORTED = 505
};

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_STATUS_H__ */
