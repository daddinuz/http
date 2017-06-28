/*
 * C Header File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmail.com
 */

#ifndef __HTTP_H__
#define __HTTP_H__

#define HTTP_VERSION "0.2.5"

#include <stdbool.h>
#include "http_status.h"
#include "http_method.h"
#include "http_request.h"
#include "http_response.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct http_params {
    bool no_follow_location;
    bool no_peer_verification;
    bool no_host_verification;
    long timeout;
} http_params_t;

/**
 * Compose and send an HTTP request.
 * If memory allocation fails, this function returns NULL, and errno is set to ENOMEM.
 *
 * @param request The HTTP request to be performed
 * @param params The request parameters
 * @return A new `http_response_t *` instance.
 */
extern http_response_t *http_perform(http_request_t *request, http_params_t *params);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_H__ */
