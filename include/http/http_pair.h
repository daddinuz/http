/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   June 22, 2017 
 * email:  daddinuz@gmal.com
 */

#ifndef __HTTP_PAIR_H__
#define __HTTP_PAIR_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Opaque structure that represents a binding between a key and a mapped value.
 */
typedef struct HttpPair HttpPair;

/**
 * Create a new pair.
 * If memory allocation fails, this function returns NULL, and errno is set to ENOMEM.
 *
 * @param key The key.
 * @param value The value associated to the key.
 * @return A new HttpPair instance or NULL if memory allocation fails.
 */
extern HttpPair *http_pair_new(char *key, char *value);

/**
 * Delete an already allocated pair.
 * Does not free the keys or values themselves.
 *
 * @param self The HttpPair instance.
 */
extern void http_pair_delete(HttpPair *self);

/**
 * Get the key of a pair.
 *
 * @param self The HttpPair instance.
 * @return The key of the pair
 */
extern char *http_pair_key(HttpPair *self);

/**
 * Get the value of a pair.
 *
 * @param self The HttpPair instance.
 * @return The value of the pair
 */
extern char *http_pair_value(HttpPair *self);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_PAIR_H__ */
