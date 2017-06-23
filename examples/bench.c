/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   February 11, 2017
 * email:  daddinuz@gmail.com
 */

#include <assert.h>
#include "http.h"

/*
 *
 */
int main() {
    HttpString url = http_string_copy("https://api.github.com/repos/daddinuz/http/issues");
    HttpDict *headers = http_dict_new();
    http_dict_set(headers, "Accept", "application/vnd.github.VERSION.raw+json");
    http_dict_set(headers, "Content-Type", "application/json");
    http_dict_set(headers, "User-Agent", "daddinuz/http");

    {
        const HttpResponse *response = http_get(url, .headers=headers);
        assert(response->status_code == HTTP_STATUS.OK);

        http_request_delete(response->request);
        http_response_delete(response);
    }

    http_dict_delete(headers);
    http_string_delete(url);
    return 0;
}
