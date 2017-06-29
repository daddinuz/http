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

typedef enum http_status {
    HTTP_STATUS_CONTINUE = 100,                         /* Continue                        */
    HTTP_STATUS_SWITCHING_PROTOCOLS = 101,              /* Switching Protocols             */
    HTTP_STATUS_PROCESSING = 102,                       /* Processing                      */
    HTTP_STATUS_OK = 200,                               /* OK                              */
    HTTP_STATUS_CREATED = 201,                          /* Created                         */
    HTTP_STATUS_ACCEPTED = 202,                         /* Accepted                        */
    HTTP_STATUS_NON_AUTHORITATIVE_INFORMATION = 203,    /* Non-Authoritative Information   */
    HTTP_STATUS_NO_CONTENT = 204,                       /* No Content                      */
    HTTP_STATUS_RESET_CONTENT = 205,                    /* Reset Content                   */
    HTTP_STATUS_PARTIAL_CONTENT = 206,                  /* Partial Content                 */
    HTTP_STATUS_MULTI_STATUS = 207,                     /* Multi-Status                    */
    HTTP_STATUS_ALREADY_REPORTED = 208,                 /* Already Reported                */
    HTTP_STATUS_IM_USED = 226,                          /* IM Used                         */
    HTTP_STATUS_MULTIPLE_CHOICES = 300,                 /* Multiple Choices                */
    HTTP_STATUS_MOVED_PERMANENTLY = 301,                /* Moved Permanently               */
    HTTP_STATUS_FOUND = 302,                            /* Found                           */
    HTTP_STATUS_SEE_OTHER = 303,                        /* See Other                       */
    HTTP_STATUS_NOT_MODIFIED = 304,                     /* Not Modified                    */
    HTTP_STATUS_USE_PROXY = 305,                        /* Use Proxy                       */
    HTTP_STATUS_TEMPORARY_REDIRECT = 307,               /* Temporary Redirect              */
    HTTP_STATUS_PERMANENT_REDIRECT = 308,               /* Permanent Redirect              */
    HTTP_STATUS_BAD_REQUEST = 400,                      /* Bad Request                     */
    HTTP_STATUS_UNAUTHORIZED = 401,                     /* Unauthorized                    */
    HTTP_STATUS_PAYMENT_REQUIRED = 402,                 /* Payment Required                */
    HTTP_STATUS_FORBIDDEN = 403,                        /* Forbidden                       */
    HTTP_STATUS_NOT_FOUND = 404,                        /* Not Found                       */
    HTTP_STATUS_METHOD_NOT_ALLOWED = 405,               /* Method Not Allowed              */
    HTTP_STATUS_NOT_ACCEPTABLE = 406,                   /* Not Acceptable                  */
    HTTP_STATUS_PROXY_AUTHENTICATION_REQUIRED = 407,    /* Proxy Authentication Required   */
    HTTP_STATUS_REQUEST_TIMEOUT = 408,                  /* Request Timeout                 */
    HTTP_STATUS_CONFLICT = 409,                         /* Conflict                        */
    HTTP_STATUS_GONE = 410,                             /* Gone                            */
    HTTP_STATUS_LENGTH_REQUIRED = 411,                  /* Length Required                 */
    HTTP_STATUS_PRECONDITION_FAILED = 412,              /* Precondition Failed             */
    HTTP_STATUS_PAYLOAD_TOO_LARGE = 413,                /* Payload Too Large               */
    HTTP_STATUS_URI_TOO_LONG = 414,                     /* URI Too Long                    */
    HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE = 415,           /* Unsupported Media Type          */
    HTTP_STATUS_RANGE_NOT_SATISFIABLE = 416,            /* Range Not Satisfiable           */
    HTTP_STATUS_EXPECTATION_FAILED = 417,               /* Expectation Failed              */
    HTTP_STATUS_MISDIRECTED_REQUEST = 421,              /* Misdirected Request             */
    HTTP_STATUS_UNPROCESSABLE_ENTITY = 422,             /* Unprocessable Entity            */
    HTTP_STATUS_LOCKED = 423,                           /* Locked                          */
    HTTP_STATUS_FAILED_DEPENDENCY = 424,                /* Failed Dependency               */
    HTTP_STATUS_UPGRADE_REQUIRED = 426,                 /* Upgrade Required                */
    HTTP_STATUS_PRECONDITION_REQUIRED = 428,            /* Precondition Required           */
    HTTP_STATUS_TOO_MANY_REQUESTS = 429,                /* Too Many Requests               */
    HTTP_STATUS_REQUEST_HEADER_FIELDS_TOO_LARGE = 431,  /* Request Header Fields Too Large */
    HTTP_STATUS_UNAVAILABLE_FOR_LEGAL_REASONS = 451,    /* Unavailable For Legal Reasons   */
    HTTP_STATUS_INTERNAL_SERVER_ERROR = 500,            /* Internal Server Error           */
    HTTP_STATUS_NOT_IMPLEMENTED = 501,                  /* Not Implemented                 */
    HTTP_STATUS_BAD_GATEWAY = 502,                      /* Bad Gateway                     */
    HTTP_STATUS_SERVICE_UNAVAILABLE = 503,              /* Service Unavailable             */
    HTTP_STATUS_GATEWAY_TIMEOUT = 504,                  /* Gateway Timeout                 */
    HTTP_STATUS_VERSION_NOT_SUPPORTED = 505,            /* HTTP Version Not Supported      */
    HTTP_STATUS_VARIANT_ALSO_NEGOTIATES = 506,          /* Variant Also Negotiates         */
    HTTP_STATUS_INSUFFICIENT_STORAGE = 507,             /* Insufficient Storage            */
    HTTP_STATUS_LOOP_DETECTED = 508,                    /* Loop Detected                   */
    HTTP_STATUS_NOT_EXTENDED = 510,                     /* Not Extended                    */
    HTTP_STATUS_NETWORK_AUTHENTICATION_REQUIRED = 511   /* Network Authentication Required */
} http_status_t;

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_STATUS_H__ */
