http
====

Http requests made easier, depends on libcurl.

```C
#include <http.h>
#include <stdio.h>
#include <stdlib.h>

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
```
