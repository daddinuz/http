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

/**
 * HttpString(s) are immutable dynamic allocated char *
 */
typedef const char *HttpString;

/**
 * Create a new string from `text`.
 *
 * @param text The text that will be copied in the string
 * @return A new HttpString instance
 */
extern HttpString http_string_new(const char *text);

/**
 * Create a new string concatenating together two strings.
 *
 * @param a The first string
 * @param b The second string
 * @return A new HttpString instance
 */
extern HttpString http_string_join(const char *a, const char *b);

/**
 * Delete an HttpString instance.
 *
 * @param self The string to be deleted
 */
extern void http_string_delete(HttpString self);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_STRING_H__ */
