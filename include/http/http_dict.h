/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   May 27, 2017 
 * email:  daddinuz@gmal.com
 */

#ifndef __HTTP_DICT_H__
#define __HTTP_DICT_H__

#include <stddef.h>
#include <stdbool.h>
#include "http_pair.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Opaque structure that represents a dict.
 */
typedef struct HttpDict HttpDict;

/**
 * Create a new HttpDict.
 * If memory allocation fails, this function returns NULL, and errno is set to ENOMEM.
 *
 * @return A new HttpDict instance or NULL if memory allocation fails.
 */
extern HttpDict *http_dict_new(void);

/**
 * Delete all entries of a dict.
 * Does not free the keys or values themselves.
 *
 * @param self The HttpDict instance.
 */
extern void http_dict_clear(HttpDict *self);

/**
 * Delete all entries of a dict and the dict itself.
 * Does not free the keys or values themselves.
 *
 * @param self The HttpDict instance.
 */
extern void http_dict_delete(HttpDict *self);

/**
 * Set value for the given key in the dict.
 * If memory allocation fails, this function returns NULL,
 * the dict's size is not increased, and errno is set to ENOMEM.
 *
 * @param self The HttpDict instance.
 * @param key The key for the given value.
 * @param value The value associated to the key.
 * @return pre-existing value for `key` if any else NULL.
 */
extern char *http_dict_set(HttpDict *self, char *key, char *value);

/**
 * Get the value associated to a key in the dict.
 *
 * @param self The HttpDict instance.
 * @param key The key to search for.
 * @param default_value The value returned if the key is not set in the dict.
 * @return `default_value` if no entry for the given key is found else value associated to `key`.
 */
extern char *http_dict_get(HttpDict *self, char *key, char *default_value);

/**
 * Test if the dict contains a key.
 *
 * @param self The HttpDict instance.
 * @param key The key to search for.
 * @return true if the dict contains an entry for the given key else false.
 */
extern bool http_dict_has(HttpDict *self, char *key);

/**
 * Remove an entry from the dict.
 * If memory allocation fails, this function returns NULL,
 * the dict's size is not decreased, and errno is set to ENOMEM.
 *
 * @param self The HttpDict instance.
 * @param key The key to be removed.
 * @return NULL if no entry for the given key is found else the removed key-value pair.
 */
extern HttpPair *http_dict_remove(HttpDict *self, char *key);

/**
 * Test if dict contains at least one entry.
 *
 * @param self The HttpDict instance.
 * @return true if at least one entry is set else false.
 */
extern bool http_dict_empty(HttpDict *self);

/**
 * Get the number of entries stored in the dict.
 *
 * @param self The HttpDict instance.
 * @return The number of entries stored in the dict.
 */
extern size_t http_dict_size(HttpDict *self);

/**
 * Invokes the given callback on each entry in the dict.
 * Stops iterating if the callback returns false.
 *
 * @param self The HttpDict instance.
 * @param callback The function to call.
 * @param context The context that will be passed to `callback`
 */
extern void http_dict_each(HttpDict *self, bool (*callback)(char *key, char *value, void *context), void *context);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_DICT_H__ */
