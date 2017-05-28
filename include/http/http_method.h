/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017 
 * email:  daddinuz@gmal.com
 */

#include "http_string.h"

#ifndef __HTTP_METHOD_H__
#define __HTTP_METHOD_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __HttpMethod {
    const HttpString GET;
    const HttpString PUT;
    const HttpString HEAD;
    const HttpString POST;
    const HttpString PATCH;
    const HttpString DELETE;
    const HttpString OPTIONS;
} __HttpMethod;

static const __HttpMethod HttpMethod = {
        .GET="GET",
        .PUT="PUT",
        .HEAD="HEAD",
        .POST="POST",
        .PATCH="PATCH",
        .DELETE="DELETE",
        .OPTIONS="OPTIONS"
};

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_METHOD_H__ */
