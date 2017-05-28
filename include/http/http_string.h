/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   May 28, 2017 
 * email:  daddinuz@gmal.com
 */

#ifndef __HTTP_STRING_H__
#define __HTTP_STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef const char *HttpString;

extern HttpString http_string_new(const char *str);
extern void http_string_delete(HttpString self);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_STRING_H__ */
