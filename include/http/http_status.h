/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017 
 * email:  daddinuz@gmail.com
 */

#ifndef __HTTP_STATUS_H__
#define __HTTP_STATUS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __HttpStatus {
    int CONTINUE;
    int SWITCHING_PROTOCOLS;
    int OK;
    int CREATED;
    int ACCEPTED;
    int NON_AUTHORITATIVE_INFORMATION;
    int NO_CONTENT;
    int RESET_CONTENT;
    int PARTIAL_CONTENT;
    int MULTIPLE_CHOICES;
    int MOVED_PERMANENTLY;
    int FOUND;
    int SEE_OTHER;
    int NOT_MODIFIED;
    int USE_PROXY;
    int TEMPORARY_REDIRECT;
    int BAD_REQUEST;
    int UNAUTHORIZED;
    int PAYMENT_REQUIRED;
    int FORBIDDEN;
    int NOT_FOUND;
    int METHOD_NOT_ALLOWED;
    int NOT_ACCEPTABLE;
    int PROXY_AUTHENTICATION_REQUIRED;
    int REQUEST_TIMEOUT;
    int CONFLICT;
    int GONE;
    int LENGTH_REQUIRED;
    int PRECONDITION_FAILED;
    int REQUEST_ENTITY_TOO_LARGE;
    int REQUEST_URI_TOO_LONG;
    int UNSUPPORTED_MEDIA_TYPE;
    int REQUESTED_RANGE_NOT_SATISFIABLE;
    int EXPECTATION_FAILED;
    int UNPROCESSABLE_ENTITY;
    int TOO_MANY_REQUESTS;
    int INTERNAL_SERVER_ERROR;
    int NOT_IMPLEMENTED;
    int BAD_GATEWAY;
    int SERVICE_UNAVAILABLE;
    int GATEWAY_TIMEOUT;
    int VERSION_NOT_SUPPORTED;
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
