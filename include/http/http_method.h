/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017 
 * email:  daddinuz@gmail.com
 */

#ifndef __HTTP_METHOD_H__
#define __HTTP_METHOD_H__

#include "http_string.h"

#ifdef __cplusplus
extern "C" {
#endif

static const struct {
    HttpString GET;
    HttpString PUT;
    HttpString HEAD;
    HttpString POST;
    HttpString PATCH;
    HttpString DELETE;
    HttpString OPTIONS;
} HTTP_METHOD = {
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
