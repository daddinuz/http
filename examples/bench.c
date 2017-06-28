/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "http.h"

/*
 *
 */
int main() {
    const char *url = "https://api.github.com/repos/daddinuz/http/issues";
    const char *headers = "Accept: application/vnd.github.VERSION.raw+json\n"
            "Content-Type: application/json\n"
            "User-Agent: daddinuz/http";

    http_request_t *request = http_request_new(HTTP_METHOD_GET, url, headers, NULL);
    printf("Request:\nmethod: %d\nurl: %s\nheaders: %s\nbody: %s\n\n\n",
           request->method, request->url, request->headers, request->body
    );

    http_response_t *response = http_perform(request, NULL);
    assert(response->status == HTTP_STATUS_OK);
    printf("Response (Request):\nmethod: %d\nurl: %s\nheaders: %s\nbody: %s\n\n",
           response->request->method, response->request->url, response->request->headers, response->request->body
    );
    printf("Response:\nurl: %s\nstatus: %d\nheaders: %s\nbody: %s\n",
           response->url, response->status, response->headers, response->body
    );

    http_request_delete(request);
    http_response_delete(response);
    return 0;
}
