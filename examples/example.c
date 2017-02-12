/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmal.com
 */

#include <stdio.h>
#include "http.h"


int main() {
    const char *url = "https://api.github.com/repos/daddinuz/http/issues";
    HttpHeader header = {
            .Accept="application/vnd.github.v3+json",
            .Content_Type="application/json",
            .User_Agent="daddinuz/http"
    };
    HttpResponse response = http_get(url, header);

    const char line[] = "---------------------------------------------------------------------------------------------";
    printf("%s\n%s\n%s\n%s\n", line, response.raw_header, response.raw_body, line);

    http_response_delete(&response);
    return 0;
}
