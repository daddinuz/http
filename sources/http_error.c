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

const Error HttpError_NetworkingError = Error_new("Networking error");
const Error HttpError_ConnectionFailed = Error_new("Connection failed");
const Error HttpError_ConnectionTimedOut = Error_new("Connection timed out");
const Error HttpError_ConnectionSSLFailed = Error_new("Connection SSL failed");
const Error HttpError_AuthenticationFailed = Error_new("Authentication failed");
const Error HttpError_UnableToResolveHost = Error_new("Unable to resolve host");
const Error HttpError_UnableToResolveProxy = Error_new("Unable to resolve proxy");
const Error HttpError_UnableToSendData = Error_new("Unable to send data");
