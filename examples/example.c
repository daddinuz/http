/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmal.com
 */

#include <stdio.h>
#include "http.h"

/*
 *
 */
int main() {
    char *url = "https://api.github.com/repos/daddinuz/http/issues";
    HttpDict headers = http_dict_create(
            http_dict_entry_create("Accept", "application/vnd.github.v3+json"),
            http_dict_entry_create("Content-Type", "application/json"),
            http_dict_entry_create("User-Agent", "daddinuz/http")
    );
    HttpResponse response = http_get(url);
    printf("url: %s\nstatus_code: %d\n\n%s\n%s\n",
           response.url, response.status_code, response.headers, response.body
    );
    http_response_destroy(&response);
    return 0;
}
