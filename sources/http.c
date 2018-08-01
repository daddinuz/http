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
#include <assert.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <panic/panic.h>

static Text emptyString = NULL;
static bool initialized = false;

static void cleanupEmptyString(void) {
    Text_delete(emptyString);
}

static Text readFile(FILE *file) {
    assert(file);
    const long start = ftell(file);
    if (start < 0) {
        Panic_terminate("Unable to determinate file size\n");
    }
    if (fseek(file, 0L, SEEK_END) != 0) {
        Panic_terminate("Unable to determinate file size\n");
    }
    const long end = ftell(file);
    if (end < 0) {
        Panic_terminate("Unable to determinate file size\n");
    }
    rewind(file);
    const size_t length = (size_t) end;
    Text text = Text_withCapacity(length);
    const size_t read = fread(text, sizeof(text[0]), length, file);
    if (read != length) {
        Panic_terminate("Unable to read file\n");
    }
    Text_setLength(text, length);
    text[length] = 0;
    return text;
}

void Http_initialize(void) {
    if (!initialized) {
        const CURLcode e = curl_global_init(CURL_GLOBAL_ALL);
        if (CURLE_OK != e) {
            Panic_terminate("Unable to initialize CURL\n%s\n", curl_easy_strerror(e));
        }
        initialized = true;
    }
}

void Http_terminate(void) {
    if (initialized) {
        curl_global_cleanup();
    }
}

TextView Http_getEmptyString(void) {
    if (NULL == emptyString) {
        emptyString = Text_new();
        atexit(cleanupEmptyString);
    }
    return emptyString;
}

Http_FireResult HttpRequest_fire(const struct HttpRequest **ref) {
    assert(ref);
    assert(*ref);
    assert(initialized);
    Error error;
    CURL *curlHandler = NULL;
    FILE *responseHeadersFile, *responseBodyFile = NULL;
    struct curl_slist *curlHeaders = NULL;
    const struct HttpRequest *request = *ref;
    struct HttpResponseBuilder *responseBuilder = HttpResponseBuilder_new(ref);

    curlHandler = curl_easy_init();
    if (NULL == curlHandler) {
        Panic_terminate("Out of memory\n");
    }

    responseHeadersFile = tmpfile();
    if (NULL == responseHeadersFile) {
        Panic_terminate("Unable to open temporary file\n");
    }

    responseBodyFile = tmpfile();
    if (NULL == responseBodyFile) {
        Panic_terminate("Unable to open temporary file\n");
    }

    if (Text_length(HttpRequest_getHeaders(request)) > 0) {
        curlHeaders = curl_slist_append(curlHeaders, HttpRequest_getHeaders(request));
        if (NULL == curlHeaders) {
            Panic_terminate("Out of memory\n");
        }
    }

    // Set request url and method
    curl_easy_setopt(curlHandler, CURLOPT_URL, HttpRequest_getUrl(request));
    curl_easy_setopt(curlHandler, CURLOPT_CUSTOMREQUEST, HttpMethod_explain(HttpRequest_getMethod(request)));

    // Set request headers
    curl_easy_setopt(curlHandler, CURLOPT_HTTPHEADER, curlHeaders);

    // Set request body
    TextView requestBody = HttpRequest_getBody(request);
    curl_easy_setopt(curlHandler, CURLOPT_POSTFIELDS, requestBody);
    curl_easy_setopt(curlHandler, CURLOPT_POSTFIELDSIZE, Text_length(requestBody));

    // Set request parameters
    curl_easy_setopt(curlHandler, CURLOPT_FOLLOWLOCATION, HttpRequest_getFollowLocation(request));
    curl_easy_setopt(curlHandler, CURLOPT_SSL_VERIFYPEER, HttpRequest_getPeerVerification(request));
    curl_easy_setopt(curlHandler, CURLOPT_SSL_VERIFYHOST, HttpRequest_getHostVerification(request));
    curl_easy_setopt(curlHandler, CURLOPT_TIMEOUT, HttpRequest_getTimeout(request));

    // Set request callbacks in order to store the response data
    curl_easy_setopt(curlHandler, CURLOPT_HEADERDATA, responseHeadersFile);
    curl_easy_setopt(curlHandler, CURLOPT_WRITEDATA, responseBodyFile);

#ifdef HTTP_DEBUG
    // Set verbose debug output
    curl_easy_setopt(curlHandler, CURLOPT_VERBOSE, 1L);
#endif

    const CURLcode e = curl_easy_perform(curlHandler);
    switch (e) {
        case CURLE_OK:
            error = Ok;
            break;
        case CURLE_COULDNT_CONNECT:
            error = HttpError_ConnectionFailed;
            break;
        case CURLE_OPERATION_TIMEDOUT:
            error = HttpError_ConnectionTimedOut;
            break;
        case CURLE_SSL_CONNECT_ERROR:
            error = HttpError_ConnectionSSLFailed;
            break;
        case CURLE_LOGIN_DENIED:
            error = HttpError_AuthenticationFailed;
            break;
        case CURLE_COULDNT_RESOLVE_HOST:
            error = HttpError_UnableToResolveHost;
            break;
        case CURLE_COULDNT_RESOLVE_PROXY:
            error = HttpError_UnableToResolveProxy;
            break;
        case CURLE_SEND_ERROR:
            error = HttpError_UnableToSendData;
            break;
        default:
            error = HttpError_NetworkingError;
    }

    // set response effective url
    if (HttpRequest_getFollowLocation(request)) {
        char *tmp = NULL;
        curl_easy_getinfo(curlHandler, CURLINFO_EFFECTIVE_URL, &tmp);
        HttpResponseBuilder_setUrl(responseBuilder, Atom_fromLiteral(tmp));
    }

    // set response status
    long responseStatus;
    curl_easy_getinfo(curlHandler, CURLINFO_RESPONSE_CODE, &responseStatus);
    HttpResponseBuilder_setStatus(responseBuilder, (enum HttpStatus) responseStatus);

    // set response headers
    Text responseHeaders = readFile(responseHeadersFile);
    HttpResponseBuilder_setHeaders(responseBuilder, &responseHeaders);

    // set response body
    Text responseBody = readFile(responseBodyFile);
    HttpResponseBuilder_setBody(responseBuilder, &responseBody);

    // perform cleanups
    curl_slist_free_all(curlHeaders);
    curl_easy_cleanup(curlHandler);
    fclose(responseHeadersFile);
    fclose(responseBodyFile);

    return Ok == error ? Http_FireResult_ok(HttpResponseBuilder_build(&responseBuilder)) : Http_FireResult_error(error);
}
