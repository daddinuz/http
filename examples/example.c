/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmail.com
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "http.h"

/*
 *
 */
int main() {
    HttpString auth_token = http_string_join("token ", getenv("GITHUB_AUTH_TOKEN"));
    HttpString base_url = http_string_copy("https://api.github.com/repos/daddinuz/http/issues");
    HttpString target_issue_url = http_string_join(base_url, "/33");
    HttpDict *headers = http_dict_new();
    const HttpResponse *response = NULL;

    http_dict_set(headers, "Authorization", (char *) auth_token);
    http_dict_set(headers, "Accept", "application/vnd.github.VERSION.raw+json");
    http_dict_set(headers, "Content-Type", "application/json");
    http_dict_set(headers, "User-Agent", "daddinuz/http");

    /**
     * Create an issue
     */
    {
        HttpString body = http_string_copy("{\"title\":\"Test issue opened with http\",\"body\":\"That's cool.\"}");

        response = http_post(base_url, .headers=headers, .body=body);
        assert(response->status_code != HTTP_STATUS.OK || response->status_code != HTTP_STATUS.CREATED);

        printf("url: %s\nstatus: %d\n\n%s\n%s\n",
               response->url, response->status_code, response->raw_headers, response->raw_body
        );

        http_request_delete(response->request);
        http_response_delete(response);
        http_string_delete(body);
    }

    /**
     * Get an issue
     */
    {
        response = http_get(target_issue_url, .headers=headers);
        assert(response->status_code != HTTP_STATUS.OK || response->status_code != HTTP_STATUS.CREATED);

        printf("url: %s\nstatus: %d\n\n%s\n%s\n",
               response->url, response->status_code, response->raw_headers, response->raw_body
        );

        http_request_delete(response->request);
        http_response_delete(response);
    }


    /**
     * Close an issue
     */
    {
        HttpString body = http_string_copy("{\"state\":\"closed\"}");

        response = http_patch(target_issue_url, .headers=headers, .body=body);
        assert(response->status_code != HTTP_STATUS.OK || response->status_code != HTTP_STATUS.CREATED);

        printf("url: %s\nstatus: %d\n\n%s\n%s\n",
               response->url, response->status_code, response->raw_headers, response->raw_body
        );

        http_request_delete(response->request);
        http_response_delete(response);
        http_string_delete(body);
    }

    http_dict_delete(headers);
    http_string_delete(target_issue_url);
    http_string_delete(base_url);
    http_string_delete(auth_token);
    return 0;
}
