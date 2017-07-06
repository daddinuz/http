/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmail.com
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "http.h"
#include "sds/sds.h"
#include "parson/parson.h"
#include "picohttpparser/picohttpparser.h"

#define MAX_HEADERS 64
#define DATE_HEADER_LEN 5

/*
 *
 */
int main() {
    sds created_at = NULL;
    sds issue_details_url = NULL;
    sds issues_list_url = sdsnew("https://api.github.com/repos/daddinuz/http/issues");
    sds headers = sdscatfmt(
            sdsempty(),
            "Authorization: token %s\n"
                    "Accept: application/vnd.github.VERSION.raw+json\n"
                    "Content-Type: application/json\n"
                    "User-Agent: daddinuz/http",
            getenv("GITHUB_AUTH_TOKEN")
    );

    /**
     * Open an issue
     */
    {
        printf("Creating a new issue... ");

        /* performing request */
        const char *body = "{\"title\":\"Test issue opened with http.\",\"body\":\"That's cool.\"}";
        http_request_t *request = http_request_new(HTTP_METHOD_POST, issues_list_url, headers, body);
        http_response_t *response = http_perform(request, NULL);
        if (response->status != HTTP_STATUS_CREATED) {
            return 1;
        }

        /* parsing headers */
        char header_name[DATE_HEADER_LEN] = {0};
        size_t response_headers_len = MAX_HEADERS;
        struct phr_header response_headers_dict[MAX_HEADERS];
        const size_t response_headers_start = strcspn(response->headers, "\n") + 1;
        const size_t response_headers_length = response->headers_length - response_headers_start;
        const char *response_headers = (response->headers + response_headers_start);
        phr_parse_headers(response_headers, response_headers_length, response_headers_dict, &response_headers_len, 0);
        struct phr_header *current_header = NULL;
        for (size_t i = 0; i < response_headers_len; i++) {
            current_header = &response_headers_dict[i];
            snprintf(header_name, DATE_HEADER_LEN, "%.*s", (int) current_header->name_len, current_header->name);
            if (strcasecmp("date", header_name) == 0) {
                created_at = sdscatprintf(sdsempty(), "%.*s", (int) current_header->value_len, current_header->value);
                break;
            }
        }

        /* parsing body */
        JSON_Value *root = json_parse_string(response->body);
        JSON_Object *object = json_value_get_object(root);
        issue_details_url = sdsnew(json_object_get_string(object, "url"));

        /* freeing memory */
        json_value_free(root);
        http_response_delete(response);
        http_request_delete(request);

        puts("done");
    }

    /**
     * Update the issue
     */
    {
        printf("Updating the issue... ");

        sds body = sdscatfmt(
                sdsempty(),
                "{\"title\":\"Test issue opened %s.\",\"body\":\"Going to close this issue.\"}",
                created_at
        );
        http_request_t *request = http_request_new(HTTP_METHOD_PATCH, issue_details_url, headers, body);
        http_response_t *response = http_perform(request, NULL);
        if (response->status != HTTP_STATUS_OK) {
            return 2;
        }
        http_response_delete(response);
        http_request_delete(request);
        sdsfree(body);

        puts("done");
    }

    /**
     * Retrieve the issue
     */
    {
        printf("Retrieving the issue... ");

        http_request_t *request = http_request_new(HTTP_METHOD_GET, issue_details_url, headers, NULL);
        http_response_t *response = http_perform(request, NULL);
        if (response->status != HTTP_STATUS_OK) {
            return 3;
        }
        http_response_delete(response);
        http_request_delete(request);

        puts("done");
    }

    /**
     * Close the issue
     */
    {
        printf("Closing the issue... ");

        const char *body = "{\"state\":\"closed\"}";
        http_request_t *request = http_request_new(HTTP_METHOD_PATCH, issue_details_url, headers, body);
        http_response_t *response = http_perform(request, NULL);
        if (response->status != HTTP_STATUS_OK) {
            return 4;
        }
        http_response_delete(response);
        http_request_delete(request);

        puts("done");
    }

    sdsfree(headers);
    sdsfree(issues_list_url);
    sdsfree(issue_details_url);
    sdsfree(created_at);
    return 0;
}
