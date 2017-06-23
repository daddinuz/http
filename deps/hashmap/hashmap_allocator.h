/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   June 08, 2017
 * email:  daddinuz@gmail.com
 */

/*
 * hashmap allocator selection.
 *
 * Update this file is in order to change at compile time the allocator that is going to be used.
 * Just define the macros below to what you want to use and include the proper files.
 * By default libc standard allocator will be used.
 */

#ifndef __HASHMAP_ALLOCATOR_H__
#define __HASHMAP_ALLOCATOR_H__

#include <stdlib.h>
#include <memory.h>

#ifdef __cplusplus
extern "C" {
#endif

#define hashmap_m_malloc(size)         malloc((size))
#define hashmap_m_calloc(size, n)      calloc((size), (n))
#define hashmap_m_ralloc(ptr, size)    realloc((ptr), (size))
#define hashmap_m_copy(dst, src, size) memcpy((dst), (src), (size))
#define hashmap_m_move(dst, src, size) memmove((dst), (src), (size))
#define hashmap_m_free(ptr)            free((ptr))

#ifdef __cplusplus
}
#endif

#endif /* __HASHMAP_ALLOCATOR_H__ */
