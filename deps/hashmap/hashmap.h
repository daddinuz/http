/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   June 08, 2017
 * email:  daddinuz@gmal.com
 */

#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Structure holding a key and a mapped value.
 */
typedef struct hashmap_pair_t {
    void *key;
    void *value;
} hashmap_pair_t;

/**
 * Create a new hash map pair.
 * If memory allocation fails, this function returns NULL, and errno is set to ENOMEM.
 *
 * @param key The key.
 * @param value The value associated to the key.
 * @return A new hash map pair instance or NULL if memory allocation fails.
 */
extern hashmap_pair_t *hashmap_pair_new(void *key, void *value);

/**
 * Delete an already allocated hash map pair.
 * Does not free the keys or values themselves.
 *
 * @param self The hashmap_pair instance.
 */
extern void hashmap_pair_delete(hashmap_pair_t *self);

/**
 * Opaque structure that represents an hash map.
 */
typedef struct hashmap_t hashmap_t;

/**
 * Create a new hash map.
 * If memory allocation fails, this function returns NULL, and errno is set to ENOMEM.
 *
 * @param initial_capacity Number of expected entries.
 * @param hash Function which hashes keys.
 * @param equals Function which compares keys for equality.
 * @return A new hash map instance or NULL if memory allocation fails.
 */
extern hashmap_t *
hashmap_new(size_t initial_capacity, int (*hash)(void *key), bool (*equals)(void *key_a, void *key_b));

/**
 * Delete entries of an hash map.
 * Does not free the keys or values themselves.
 *
 * @param self The hashmap instance.
 */
extern void hashmap_clear(hashmap_t *self);

/**
 * Delete an hash map.
 * Does not free the keys or values themselves.
 *
 * @param self The hashmap instance.
 */
extern void hashmap_delete(hashmap_t *self);

/**
 * Set value for the given key in the map.
 * If memory allocation fails, this function returns NULL,
 * the map's size is not increased, and errno is set to ENOMEM.
 *
 * @param self The hashmap instance.
 * @param key The key for the given value.
 * @param value The value associated to the key.
 * @return pre-existing value for `key` if any else NULL.
 */
extern void *hashmap_set(hashmap_t *self, void *key, void *value);

/**
 * Get the value associated to a key in the map.
 *
 * @param self The hashmap instance.
 * @param key The key to search for.
 * @param default_value The value returned if the key is not set in the map.
 * @return `default_value` if no entry for the given key is found else value associated to `key`.
 */
extern void *hashmap_get(hashmap_t *self, void *key, void *default_value);

/**
 * Test if the map contains a key.
 *
 * @param self The hashmap instance.
 * @param key The key to search for.
 * @return true if the map contains an entry for the given key else false.
 */
extern bool hashmap_has(hashmap_t *self, void *key);

/**
 * Remove an entry from the map.
 * If memory allocation fails, this function returns NULL,
 * the map's size is not decreased, and errno is set to ENOMEM.
 *
 * @param self The hashmap instance.
 * @param key The key to be removed.
 * @return NULL if no entry for the given key is found else the removed key-value pair.
 */
extern hashmap_pair_t *hashmap_remove(hashmap_t *self, void *key);

/**
 * Test if map contains at least one entry.
 *
 * @param self The hashmap instance.
 * @return true if at least one entry is set else false.
 */
extern bool hashmap_empty(hashmap_t *self);

/**
 * Get the number of entries stored in the map.
 *
 * @param self The hashmap instance.
 * @return The number of entries stored in the hashmap.
 */
extern size_t hashmap_size(hashmap_t *self);

/**
 * Get the number of entries that could be stored in the hashmap without reallocations.
 *
 * @param self The hashmap instance.
 * @return The number of entries that could be stored in the hashmap without reallocations.
 */
extern size_t hashmap_capacity(hashmap_t *self);

/**
 * Invokes the given callback on each entry in the map.
 * Stops iterating if the callback returns false.
 *
 * @param self The hashmap instance.
 * @param callback The function to call.
 * @param context The context that will be passed to `callback`
 */
extern void hashmap_each(hashmap_t *self, bool (*callback)(void *key, void *value, void *context), void *context);

/**
 * Counts the number of entry collisions.
 *
 * @param self The hashmap instance.
 * @return The number of collisions.
 */
extern size_t hashmap_count_collisions(hashmap_t *self);

#ifdef __cplusplus
}
#endif

#endif /* __HASHMAP_H__ */
