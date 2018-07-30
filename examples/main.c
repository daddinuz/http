/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <http.h>
#include <stdio.h>
#include <stdlib.h>

#define truth(x) \
    (((x)) ? "true" : "false")

static void
printRequest(const struct HttpRequest *request)
__attribute__((__nonnull__));

static void
printResponse(const struct HttpResponse *response)
__attribute__((__nonnull__));

int main() {
    Http_initialize();

    Atom url = Atom_fromLiteral("https://api.github.com/repos/daddinuz/http/issues");
    struct HttpRequestBuilder *requestBuilder = HttpRequestBuilder_new(HTTP_METHOD_GET, url);
    HttpRequestBuilder_setTimeout(requestBuilder, 25);
    HttpRequestBuilder_emplaceHeaders(requestBuilder,
                                      "Authorization: token %s\n"
                                      "Accept: application/vnd.github.VERSION.raw+json\n"
                                      "Content-Type: application/json\n"
                                      "User-Agent: daddinuz/http\n",
                                      getenv("GITHUB_AUTH_TOKEN"));

    const struct HttpRequest *request = HttpRequestBuilder_build(&requestBuilder);
    printRequest(request);

    const struct HttpResponse *response = Http_FireResult_unwrap(HttpRequest_fire(&request));
    printResponse(response);

    HttpResponse_delete(response);
    Http_terminate();
    return 0;
}

/*
 *
 */
void printRequest(const struct HttpRequest *request) {
    printf("\n"
           "method: %s\n"
           "url: %s\n"
           "headers:\n---------------------------------------\n%s\n---------------------------------------\n"
           "body:\n---------------------------------------\n%s\n---------------------------------------\n"
           "timeout: %ld\n"
           "followLocation: %s\n"
           "peerVerification: %s\n"
           "hostVerification: %s\n"
           "\n",
           HttpMethod_explain(HttpRequest_getMethod(request)),
           HttpRequest_getUrl(request),
           HttpRequest_getHeaders(request),
           HttpRequest_getBody(request),
           HttpRequest_getTimeout(request),
           truth(HttpRequest_getFollowLocation(request)),
           truth(HttpRequest_getPeerVerification(request)),
           truth(HttpRequest_getHostVerification(request))
    );
}

void printResponse(const struct HttpResponse *response) {
    printf("\n"
           "status: %d %s\n"
           "effectiveUrl: %s\n"
           "headers:\n---------------------------------------\n%s\n---------------------------------------\n"
           "body:\n---------------------------------------\n%s\n---------------------------------------\n"
           "\n",
           HttpResponse_getStatus(response), HttpStatus_explain(HttpResponse_getStatus(response)),
           HttpResponse_getUrl(response),
           HttpResponse_getHeaders(response),
           HttpResponse_getBody(response)
    );
}
