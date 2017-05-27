/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017 
 * email:  daddinuz@gmal.com
 */

#ifndef __HTTP_METHOD_H__
#define __HTTP_METHOD_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __HttpMethod {
    const char *GET;
    const char *PUT;
    const char *HEAD;
    const char *POST;
    const char *PATCH;
    const char *DELETE;
    const char *OPTIONS;
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
