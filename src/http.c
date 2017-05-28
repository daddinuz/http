/*
 * C Source File
 *
 * Author: Davide Di Carlo
 * Date:   May 26, 2017 
 * email:  daddinuz@gmal.com
 */

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "http.h"

#define _STR(x)         #x
#define STR(x)          _STR(x)
#define TRACE(x)        "\nAt: " __FILE__ ":" STR(__LINE__) "\n" x

#define BUFFER_SIZE     512

/*
 *
 */
static size_t __write_headers_callback(void *data, size_t size, size_t nmemb, HttpResponse *response);
static size_t __write_body_callback(void *data, size_t size, size_t nmemb, HttpResponse *response);

/*
 *
 */
HttpResponse http_perform(HttpRequest request, bool allow_redirects, long timeout) {
    char buffer[BUFFER_SIZE] = {0};
    CURL *handler = curl_easy_init();
    struct curl_slist *headers_list = NULL;
    HttpResponse response = http_response_create(0, NULL, NULL, 0, NULL, 0);

    if (NULL == handler) {
        perror(TRACE("Error"));
        abort();
    }

    /* setup headers */
    if (request.headers) {
        HttpDictEntry header_entry = request.headers[0];
        for (size_t i = 0; header_entry.key && header_entry.value; i++, header_entry = request.headers[i]) {
            snprintf(buffer, BUFFER_SIZE, "%s: %s", header_entry.key, header_entry.value);
            headers_list = curl_slist_append(headers_list, buffer);
        }
    }

    /* Set request options */
    curl_easy_setopt(handler, CURLOPT_URL, request.url);
    curl_easy_setopt(handler, CURLOPT_FOLLOWLOCATION, allow_redirects);
    curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, request.method);
    curl_easy_setopt(handler, CURLOPT_HTTPHEADER, headers_list);
    curl_easy_setopt(handler, CURLOPT_HEADERFUNCTION, __write_headers_callback);
    curl_easy_setopt(handler, CURLOPT_HEADERDATA, &response);
    curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, __write_body_callback);
    curl_easy_setopt(handler, CURLOPT_WRITEDATA, &response);
    if (timeout > 0) {
        curl_easy_setopt(handler, CURLOPT_TIMEOUT, timeout);
    }

#ifndef NDEBUG
    /* Get verbose debug output */
    curl_easy_setopt(handler, CURLOPT_VERBOSE, 1L);
#endif

    /* Perform the request */
    CURLcode err = curl_easy_perform(handler);
    if (CURLE_OK != err) {
        fprintf(stderr, TRACE("Error: %s\n"), curl_easy_strerror(err));
        abort();
    }

    /* Get the response info */
    char *url;
    if (allow_redirects) {
        curl_easy_getinfo(handler, CURLINFO_EFFECTIVE_URL, &url);
    } else {
        url = request.url;
    }
    response.url = strdup(url);
    curl_easy_getinfo(handler, CURLINFO_RESPONSE_CODE, &response.status_code);

    /* Terminate */
    curl_easy_cleanup(handler);
    curl_slist_free_all(headers_list);

    return response;
}

HttpResponse __http_get(const char *url, HttpXParams x_params) {
    HttpRequest request = http_request_create(HttpMethod.GET, url, x_params.headers, NULL);
    return http_perform(request, x_params.allow_redirects, x_params.timeout);
}

HttpResponse __http_head(const char *url, HttpXParams x_params) {
    HttpRequest request = http_request_create(HttpMethod.HEAD, url, x_params.headers, NULL);
    return http_perform(request, x_params.allow_redirects, x_params.timeout);
}

HttpResponse __http_delete(const char *url, HttpXParams x_params) {
    HttpRequest request = http_request_create(HttpMethod.DELETE, url, x_params.headers, NULL);
    return http_perform(request, x_params.allow_redirects, x_params.timeout);
}

HttpResponse __http_options(const char *url, HttpXParams x_params) {
    HttpRequest request = http_request_create(HttpMethod.OPTIONS, url, x_params.headers, NULL);
    return http_perform(request, x_params.allow_redirects, x_params.timeout);
}

HttpResponse __http_put(const char *url, HttpXParams x_params) {
    HttpRequest request = http_request_create(HttpMethod.PUT, url, x_params.headers, x_params.body);
    return http_perform(request, x_params.allow_redirects, x_params.timeout);
}

HttpResponse __http_post(const char *url, HttpXParams x_params) {
    HttpRequest request = http_request_create(HttpMethod.POST, url, x_params.headers, x_params.body);
    return http_perform(request, x_params.allow_redirects, x_params.timeout);
}

HttpResponse __http_patch(const char *url, HttpXParams x_params) {
    HttpRequest request = http_request_create(HttpMethod.PATCH, url, x_params.headers, x_params.body);
    return http_perform(request, x_params.allow_redirects, x_params.timeout);
}

/*
 *
 */
size_t __write_headers_callback(void *data, size_t size, size_t nmemb, HttpResponse *response) {
    const size_t actual_size = size * nmemb;
    /* realloc behaves like malloc if NULL is passed as arg */
    response->headers = realloc(response->headers, response->headers_length + actual_size + 1); /* +1 for '\0' */
    if (NULL == response->headers) {
        perror(TRACE("Error"));
        abort();
    }
    memcpy(&response->headers[response->headers_length], data, actual_size);
    response->headers_length += actual_size;
    response->headers[response->headers_length] = '\0';
    return actual_size;
}

size_t __write_body_callback(void *data, size_t size, size_t nmemb, HttpResponse *response) {
    const size_t actual_size = size * nmemb;
    /* realloc behaves like malloc if NULL is passed as arg */
    response->body = realloc(response->body, response->body_length + actual_size + 1); /* +1 for '\0' */
    if (NULL == response->body) {
        perror(TRACE("Error"));
        abort();
    }
    memcpy(&response->body[response->body_length], data, actual_size);
    response->body_length += actual_size;
    response->body[response->body_length] = '\0';
    return actual_size;
}
