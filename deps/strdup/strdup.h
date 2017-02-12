/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   February 12, 2017 
 * email:  daddinuz@gmal.com
 */

#include <stddef.h>

#ifndef __STRDUP_H__
#define __STRDUP_H__

#define STRDUP_VERSION "0.1.0"

#ifdef __cplusplus
extern "C" {
#endif

extern char *strdup(const char *s);
extern char *strndup(const char *s, size_t n);

#ifdef __cplusplus
}
#endif

#endif /* __STRDUP_H__ */
