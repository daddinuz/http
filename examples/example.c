/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmal.com
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "http.h"

/*
 *
 */
int main() {
    char url[64] = {0};
    char auth_token[64] = {0};
    HttpResponse *response = NULL;
    HttpDict headers = http_dict_create(
            http_dict_entry_create("Authorization", auth_token),
            http_dict_entry_create("Accept", "application/vnd.github.VERSION.raw+json"),
            http_dict_entry_create("Content-Type", "application/json"),
            http_dict_entry_create("User-Agent", "daddinuz/http")
    );

    strcpy(url, "https://api.github.com/repos/daddinuz/http/issues");
    sprintf(auth_token, "token %s", getenv("GITHUB_AUTH_TOKEN"));

    /**
     * Create an issue
     */
    {
        const char *body = "{\"title\":\"Test issue opened with http\",\"body\":\"That's cool.\"}";

        response = http_post(url, .headers=headers, .body=body);
        printf("url: %s\nstatus_code: %d\n\n%s\n%s\n",
               response->url, response->status_code, response->raw_headers, response->raw_body
        );

        http_request_delete(response->request);
        http_response_delete(response);
    }

    strcat(url, "/10");

    /**
     * Get an issue
     */
    {
        response = http_get(url, .headers=headers);
        printf("url: %s\nstatus_code: %d\n\n%s\n%s\n",
               response->url, response->status_code, response->raw_headers, response->raw_body
        );

        http_request_delete(response->request);
        http_response_delete(response);
    }


    /**
     * Close an issue
     */
    {
        const char *body = "{\"state\":\"closed\"}";

        response = http_patch(url, .headers=headers, .body=body);
        printf("url: %s\nstatus_code: %d\n\n%s\n%s\n",
               response->url, response->status_code, response->raw_headers, response->raw_body
        );

        http_request_delete(response->request);
        http_response_delete(response);
    }

    return 0;
}
