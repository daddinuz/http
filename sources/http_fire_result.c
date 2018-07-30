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
#include <panic/panic.h>

Http_FireResult Http_FireResult_ok(const struct HttpResponse *response) {
    assert(response);
    return (Http_FireResult) {.__response=response, .__isOk=true};
}

Http_FireResult Http_FireResult_error(Error error) {
    assert(error);
    return (Http_FireResult) {.__error=error, .__isOk=false};
}

const struct HttpResponse *__Http_FireResult_unwrap(const char *file, int line, const Http_FireResult self) {
    assert(file);
    if (Http_FireResult_isOk(self)) {
        return self.__response;
    }
    __Panic_terminate(file, line, "Error: %s.\n", Error_explain(self.__error));
}

Error __Http_FireResult_unwrapError(const char *file, int line, const Http_FireResult self) {
    assert(file);
    if (Http_FireResult_isError(self)) {
        return self.__error;
    }
    __Panic_terminate(file, line, "Error: %s.\n", "Unable to unwrap error");
}

bool Http_FireResult_isOk(const Http_FireResult self) {
    return self.__isOk;
}

bool Http_FireResult_isError(const Http_FireResult self) {
    return !self.__isOk;
}
