/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmail.com
 */

#ifndef NDEBUG
#include <stdio.h>
#endif

#include <stdlib.h>
#include "http.h"

/*
 *
 */
int main() {
    int status = 0;
    const char *url = "https://api.github.com/repos/daddinuz/http/issues";
    const char *headers = "Accept: application/vnd.github.VERSION.raw+json\n"
            "Content-Type: application/json\n"
            "User-Agent: daddinuz/http";

    http_request_t *request = http_request_new(HTTP_METHOD_GET, url, headers, NULL);
#ifndef NDEBUG
    printf("[ Request ]\n>>> method: %d\n>>> url: %s\n>>> headers:\n%s\n>>> body:\n%s\n\n\n",
           request->method, request->url, request->headers, request->body
    );
#endif
    http_response_t *response = http_perform(request, NULL);
    status = response->status;
#ifndef NDEBUG
    printf("[ Response (Request) ]\n>>> method: %d\n>>> url: %s\n>>> headers:\n%s\n>>> body:\n%s\n\n",
           response->request->method, response->request->url, response->request->headers, response->request->body
    );
    printf("[ Response ]\n>>> url: %s\n>>> status: %d\n>>> headers:\n%s\n>>> body:\n%s\n",
           response->url, response->status, response->headers, response->body
    );
#endif
    http_request_delete(request);
    http_response_delete(response);
    return !(HTTP_STATUS_OK == status);
}
