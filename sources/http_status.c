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
#include <panic/panic.h>

static const char HTTP_STATUS_CONTINUE_EXPLANATION[] = "Continue";
static const char HTTP_STATUS_SWITCHING_PROTOCOLS_EXPLANATION[] = "Switching Protocols";
static const char HTTP_STATUS_PROCESSING_EXPLANATION[] = "Processing";
static const char HTTP_STATUS_OK_EXPLANATION[] = "OK";
static const char HTTP_STATUS_CREATED_EXPLANATION[] = "Created";
static const char HTTP_STATUS_ACCEPTED_EXPLANATION[] = "Accepted";
static const char HTTP_STATUS_NON_AUTHORITATIVE_INFORMATION_EXPLANATION[] = "Non-Authoritative Information";
static const char HTTP_STATUS_NO_CONTENT_EXPLANATION[] = "No Content";
static const char HTTP_STATUS_RESET_CONTENT_EXPLANATION[] = "Reset Content";
static const char HTTP_STATUS_PARTIAL_CONTENT_EXPLANATION[] = "Partial Content";
static const char HTTP_STATUS_MULTI_STATUS_EXPLANATION[] = "Multi-Status";
static const char HTTP_STATUS_ALREADY_REPORTED_EXPLANATION[] = "Already Reported";
static const char HTTP_STATUS_IM_USED_EXPLANATION[] = "IM Used";
static const char HTTP_STATUS_MULTIPLE_CHOICES_EXPLANATION[] = "Multiple Choices";
static const char HTTP_STATUS_MOVED_PERMANENTLY_EXPLANATION[] = "Moved Permanently";
static const char HTTP_STATUS_FOUND_EXPLANATION[] = "Found";
static const char HTTP_STATUS_SEE_OTHER_EXPLANATION[] = "See Other";
static const char HTTP_STATUS_NOT_MODIFIED_EXPLANATION[] = "Not Modified";
static const char HTTP_STATUS_USE_PROXY_EXPLANATION[] = "Use Proxy";
static const char HTTP_STATUS_TEMPORARY_REDIRECT_EXPLANATION[] = "Temporary Redirect";
static const char HTTP_STATUS_PERMANENT_REDIRECT_EXPLANATION[] = "Permanent Redirect";
static const char HTTP_STATUS_BAD_REQUEST_EXPLANATION[] = "Bad Request";
static const char HTTP_STATUS_UNAUTHORIZED_EXPLANATION[] = "Unauthorized";
static const char HTTP_STATUS_PAYMENT_REQUIRED_EXPLANATION[] = "Payment Required";
static const char HTTP_STATUS_FORBIDDEN_EXPLANATION[] = "Forbidden";
static const char HTTP_STATUS_NOT_FOUND_EXPLANATION[] = "Not Found";
static const char HTTP_STATUS_METHOD_NOT_ALLOWED_EXPLANATION[] = "Method Not Allowed";
static const char HTTP_STATUS_NOT_ACCEPTABLE_EXPLANATION[] = "Not Acceptable";
static const char HTTP_STATUS_PROXY_AUTHENTICATION_REQUIRED_EXPLANATION[] = "Proxy Authentication Required";
static const char HTTP_STATUS_REQUEST_TIMEOUT_EXPLANATION[] = "Request Timeout";
static const char HTTP_STATUS_CONFLICT_EXPLANATION[] = "Conflict";
static const char HTTP_STATUS_GONE_EXPLANATION[] = "Gone";
static const char HTTP_STATUS_LENGTH_REQUIRED_EXPLANATION[] = "Length Required";
static const char HTTP_STATUS_PRECONDITION_FAILED_EXPLANATION[] = "Precondition Failed";
static const char HTTP_STATUS_PAYLOAD_TOO_LARGE_EXPLANATION[] = "Payload Too Large";
static const char HTTP_STATUS_URI_TOO_LONG_EXPLANATION[] = "URI Too Long";
static const char HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE_EXPLANATION[] = "Unsupported Media Type";
static const char HTTP_STATUS_RANGE_NOT_SATISFIABLE_EXPLANATION[] = "Range Not Satisfiable";
static const char HTTP_STATUS_EXPECTATION_FAILED_EXPLANATION[] = "Expectation Failed";
static const char HTTP_STATUS_MISDIRECTED_REQUEST_EXPLANATION[] = "Misdirected Request";
static const char HTTP_STATUS_UNPROCESSABLE_ENTITY_EXPLANATION[] = "Unprocessable Entity";
static const char HTTP_STATUS_LOCKED_EXPLANATION[] = "Locked";
static const char HTTP_STATUS_FAILED_DEPENDENCY_EXPLANATION[] = "Failed Dependency";
static const char HTTP_STATUS_UPGRADE_REQUIRED_EXPLANATION[] = "Upgrade Required";
static const char HTTP_STATUS_PRECONDITION_REQUIRED_EXPLANATION[] = "Precondition Required";
static const char HTTP_STATUS_TOO_MANY_REQUESTS_EXPLANATION[] = "Too Many Requests";
static const char HTTP_STATUS_REQUEST_HEADER_FIELDS_TOO_LARGE_EXPLANATION[] = "Request Header Fields Too Large";
static const char HTTP_STATUS_UNAVAILABLE_FOR_LEGAL_REASONS_EXPLANATION[] = "Unavailable For Legal Reasons";
static const char HTTP_STATUS_INTERNAL_SERVER_ERROR_EXPLANATION[] = "Internal Server Error";
static const char HTTP_STATUS_NOT_IMPLEMENTED_EXPLANATION[] = "Not Implemented";
static const char HTTP_STATUS_BAD_GATEWAY_EXPLANATION[] = "Bad Gateway";
static const char HTTP_STATUS_SERVICE_UNAVAILABLE_EXPLANATION[] = "Service Unavailable";
static const char HTTP_STATUS_GATEWAY_TIMEOUT_EXPLANATION[] = "Gateway Timeout";
static const char HTTP_STATUS_VERSION_NOT_SUPPORTED_EXPLANATION[] = "HTTP Version Not Supported";
static const char HTTP_STATUS_VARIANT_ALSO_NEGOTIATES_EXPLANATION[] = "Variant Also Negotiates";
static const char HTTP_STATUS_INSUFFICIENT_STORAGE_EXPLANATION[] = "Insufficient Storage";
static const char HTTP_STATUS_LOOP_DETECTED_EXPLANATION[] = "Loop Detected";
static const char HTTP_STATUS_NOT_EXTENDED_EXPLANATION[] = "Not Extended";
static const char HTTP_STATUS_NETWORK_AUTHENTICATION_REQUIRED_EXPLANATION[] = "Authentication Required";

const char *HttpStatus_explain(enum HttpStatus status) {
    switch (status) {
        case HTTP_STATUS_CONTINUE:
            return HTTP_STATUS_CONTINUE_EXPLANATION;
        case HTTP_STATUS_SWITCHING_PROTOCOLS:
            return HTTP_STATUS_SWITCHING_PROTOCOLS_EXPLANATION;
        case HTTP_STATUS_PROCESSING:
            return HTTP_STATUS_PROCESSING_EXPLANATION;
        case HTTP_STATUS_OK:
            return HTTP_STATUS_OK_EXPLANATION;
        case HTTP_STATUS_CREATED:
            return HTTP_STATUS_CREATED_EXPLANATION;
        case HTTP_STATUS_ACCEPTED:
            return HTTP_STATUS_ACCEPTED_EXPLANATION;
        case HTTP_STATUS_NON_AUTHORITATIVE_INFORMATION:
            return HTTP_STATUS_NON_AUTHORITATIVE_INFORMATION_EXPLANATION;
        case HTTP_STATUS_NO_CONTENT:
            return HTTP_STATUS_NO_CONTENT_EXPLANATION;
        case HTTP_STATUS_RESET_CONTENT:
            return HTTP_STATUS_RESET_CONTENT_EXPLANATION;
        case HTTP_STATUS_PARTIAL_CONTENT:
            return HTTP_STATUS_PARTIAL_CONTENT_EXPLANATION;
        case HTTP_STATUS_MULTI_STATUS:
            return HTTP_STATUS_MULTI_STATUS_EXPLANATION;
        case HTTP_STATUS_ALREADY_REPORTED:
            return HTTP_STATUS_ALREADY_REPORTED_EXPLANATION;
        case HTTP_STATUS_IM_USED:
            return HTTP_STATUS_IM_USED_EXPLANATION;
        case HTTP_STATUS_MULTIPLE_CHOICES:
            return HTTP_STATUS_MULTIPLE_CHOICES_EXPLANATION;
        case HTTP_STATUS_MOVED_PERMANENTLY:
            return HTTP_STATUS_MOVED_PERMANENTLY_EXPLANATION;
        case HTTP_STATUS_FOUND:
            return HTTP_STATUS_FOUND_EXPLANATION;
        case HTTP_STATUS_SEE_OTHER:
            return HTTP_STATUS_SEE_OTHER_EXPLANATION;
        case HTTP_STATUS_NOT_MODIFIED:
            return HTTP_STATUS_NOT_MODIFIED_EXPLANATION;
        case HTTP_STATUS_USE_PROXY:
            return HTTP_STATUS_USE_PROXY_EXPLANATION;
        case HTTP_STATUS_TEMPORARY_REDIRECT:
            return HTTP_STATUS_TEMPORARY_REDIRECT_EXPLANATION;
        case HTTP_STATUS_PERMANENT_REDIRECT:
            return HTTP_STATUS_PERMANENT_REDIRECT_EXPLANATION;
        case HTTP_STATUS_BAD_REQUEST:
            return HTTP_STATUS_BAD_REQUEST_EXPLANATION;
        case HTTP_STATUS_UNAUTHORIZED:
            return HTTP_STATUS_UNAUTHORIZED_EXPLANATION;
        case HTTP_STATUS_PAYMENT_REQUIRED:
            return HTTP_STATUS_PAYMENT_REQUIRED_EXPLANATION;
        case HTTP_STATUS_FORBIDDEN:
            return HTTP_STATUS_FORBIDDEN_EXPLANATION;
        case HTTP_STATUS_NOT_FOUND:
            return HTTP_STATUS_NOT_FOUND_EXPLANATION;
        case HTTP_STATUS_METHOD_NOT_ALLOWED:
            return HTTP_STATUS_METHOD_NOT_ALLOWED_EXPLANATION;
        case HTTP_STATUS_NOT_ACCEPTABLE:
            return HTTP_STATUS_NOT_ACCEPTABLE_EXPLANATION;
        case HTTP_STATUS_PROXY_AUTHENTICATION_REQUIRED:
            return HTTP_STATUS_PROXY_AUTHENTICATION_REQUIRED_EXPLANATION;
        case HTTP_STATUS_REQUEST_TIMEOUT:
            return HTTP_STATUS_REQUEST_TIMEOUT_EXPLANATION;
        case HTTP_STATUS_CONFLICT:
            return HTTP_STATUS_CONFLICT_EXPLANATION;
        case HTTP_STATUS_GONE:
            return HTTP_STATUS_GONE_EXPLANATION;
        case HTTP_STATUS_LENGTH_REQUIRED:
            return HTTP_STATUS_LENGTH_REQUIRED_EXPLANATION;
        case HTTP_STATUS_PRECONDITION_FAILED:
            return HTTP_STATUS_PRECONDITION_FAILED_EXPLANATION;
        case HTTP_STATUS_PAYLOAD_TOO_LARGE:
            return HTTP_STATUS_PAYLOAD_TOO_LARGE_EXPLANATION;
        case HTTP_STATUS_URI_TOO_LONG:
            return HTTP_STATUS_URI_TOO_LONG_EXPLANATION;
        case HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE:
            return HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE_EXPLANATION;
        case HTTP_STATUS_RANGE_NOT_SATISFIABLE:
            return HTTP_STATUS_RANGE_NOT_SATISFIABLE_EXPLANATION;
        case HTTP_STATUS_EXPECTATION_FAILED:
            return HTTP_STATUS_EXPECTATION_FAILED_EXPLANATION;
        case HTTP_STATUS_MISDIRECTED_REQUEST:
            return HTTP_STATUS_MISDIRECTED_REQUEST_EXPLANATION;
        case HTTP_STATUS_UNPROCESSABLE_ENTITY:
            return HTTP_STATUS_UNPROCESSABLE_ENTITY_EXPLANATION;
        case HTTP_STATUS_LOCKED:
            return HTTP_STATUS_LOCKED_EXPLANATION;
        case HTTP_STATUS_FAILED_DEPENDENCY:
            return HTTP_STATUS_FAILED_DEPENDENCY_EXPLANATION;
        case HTTP_STATUS_UPGRADE_REQUIRED:
            return HTTP_STATUS_UPGRADE_REQUIRED_EXPLANATION;
        case HTTP_STATUS_PRECONDITION_REQUIRED:
            return HTTP_STATUS_PRECONDITION_REQUIRED_EXPLANATION;
        case HTTP_STATUS_TOO_MANY_REQUESTS:
            return HTTP_STATUS_TOO_MANY_REQUESTS_EXPLANATION;
        case HTTP_STATUS_REQUEST_HEADER_FIELDS_TOO_LARGE:
            return HTTP_STATUS_REQUEST_HEADER_FIELDS_TOO_LARGE_EXPLANATION;
        case HTTP_STATUS_UNAVAILABLE_FOR_LEGAL_REASONS:
            return HTTP_STATUS_UNAVAILABLE_FOR_LEGAL_REASONS_EXPLANATION;
        case HTTP_STATUS_INTERNAL_SERVER_ERROR:
            return HTTP_STATUS_INTERNAL_SERVER_ERROR_EXPLANATION;
        case HTTP_STATUS_NOT_IMPLEMENTED:
            return HTTP_STATUS_NOT_IMPLEMENTED_EXPLANATION;
        case HTTP_STATUS_BAD_GATEWAY:
            return HTTP_STATUS_BAD_GATEWAY_EXPLANATION;
        case HTTP_STATUS_SERVICE_UNAVAILABLE:
            return HTTP_STATUS_SERVICE_UNAVAILABLE_EXPLANATION;
        case HTTP_STATUS_GATEWAY_TIMEOUT:
            return HTTP_STATUS_GATEWAY_TIMEOUT_EXPLANATION;
        case HTTP_STATUS_VERSION_NOT_SUPPORTED:
            return HTTP_STATUS_VERSION_NOT_SUPPORTED_EXPLANATION;
        case HTTP_STATUS_VARIANT_ALSO_NEGOTIATES:
            return HTTP_STATUS_VARIANT_ALSO_NEGOTIATES_EXPLANATION;
        case HTTP_STATUS_INSUFFICIENT_STORAGE:
            return HTTP_STATUS_INSUFFICIENT_STORAGE_EXPLANATION;
        case HTTP_STATUS_LOOP_DETECTED:
            return HTTP_STATUS_LOOP_DETECTED_EXPLANATION;
        case HTTP_STATUS_NOT_EXTENDED:
            return HTTP_STATUS_NOT_EXTENDED_EXPLANATION;
        case HTTP_STATUS_NETWORK_AUTHENTICATION_REQUIRED:
            return HTTP_STATUS_NETWORK_AUTHENTICATION_REQUIRED_EXPLANATION;
        default:
            Panic_terminate("Unknown status: %d", status);
    }
}
