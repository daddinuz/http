/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017 
 * email:  daddinuz@gmal.com
 */

#ifndef __HTTP_HEADER_H__
#define __HTTP_HEADER_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * X Macro trick to load headers keys at compile time
 */
typedef struct HttpHeader {
#include "__x_http_header__"

#define __X__(__key__) \
    char *__key__;
    __X_HTTP_HEADER__
#undef __X__

#undef __X_HTTP_HEADER__
} HttpHeader;

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_HEADER_H__ */
