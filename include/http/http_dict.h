/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   May 27, 2017 
 * email:  daddinuz@gmal.com
 */

#ifndef __HTTP_DICT_H__
#define __HTTP_DICT_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HttpDictEntry {
    char *key;
    char *value;
} HttpDictEntry;

typedef HttpDictEntry HttpDict[];

#define http_dict_entry_create(_XKey, _XValue)  (HttpDictEntry) {.key=(_XKey), .value=(_XValue)}
#define http_dict_create(...)                   {__VA_ARGS__, {0}}

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_DICT_H__ */
