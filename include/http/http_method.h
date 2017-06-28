/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017 
 * email:  daddinuz@gmail.com
 */

#ifndef __HTTP_METHOD_H__
#define __HTTP_METHOD_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum http_method {
    HTTP_METHOD_GET,
    HTTP_METHOD_PUT,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_POST,
    HTTP_METHOD_PATCH,
    HTTP_METHOD_DELETE,
    HTTP_METHOD_OPTIONS
} http_method_t;

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_METHOD_H__ */
