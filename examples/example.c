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
#include "sds.h"
#include "http.h"

/*
 *
 */
int main() {
    sds url = sdsnew("https://api.github.com/repos/daddinuz/http/issues");
    sds headers = sdscatprintf(
            sdsempty(),
            "Authorization: token %s\nAccept: application/vnd.github.VERSION.raw+json\nContent-Type: application/json\nUser-Agent: daddinuz/http",
            getenv("GITHUB_AUTH_TOKEN")
    );

    /**
     * Create an issue
     */
    {
        sds body = sdsnew("{\"title\":\"Test issue opened with http\",\"body\":\"That's cool.\"}");

        http_request_t *request = http_request_new(HTTP_METHOD_POST, url, headers, body);
        printf("Request:\nmethod: %d\nurl: %s\nheaders: %s\nbody: %s\n\n\n",
               request->method, request->url, request->headers, request->body
        );

        http_response_t *response = http_perform(request, NULL);
        assert(response->status == HTTP_STATUS_CREATED);
        printf("Response (Request):\nmethod: %d\nurl: %s\nheaders: %s\nbody: %s\n\n",
               response->request->method, response->request->url, response->request->headers, response->request->body
        );
        printf("Response:\nurl: %s\nstatus: %d\nheaders: %s\nbody: %s\n",
               response->url, response->status, response->headers, response->body
        );

        http_response_delete(response);
        http_request_delete(request);
        sdsfree(body);
    }

    url = sdscat(url, "/39");

    /**
     * Get an issue
     */
    {
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

        http_response_delete(response);
        http_request_delete(request);
    }

    /**
     * Close an issue
     */
    {
        sds body = sdsnew("{\"state\":\"closed\"}");

        http_request_t *request = http_request_new(HTTP_METHOD_PATCH, url, headers, body);
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

        http_response_delete(response);
        http_request_delete(request);
        sdsfree(body);
    }

    sdsfree(headers);
    sdsfree(url);
    return 0;
}
