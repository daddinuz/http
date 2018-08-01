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
#include <traits/traits.h>
#include <unit/features/http_fire_result.h>

Feature(Http_FireResult_ok) {
    const struct HttpRequest *request = traits_unit_get_context();
    const struct HttpResponse *response = NULL;

    {
        const size_t counter = traits_unit_get_wrapped_signals_counter();

        traits_unit_wraps(SIGABRT) {
            Http_FireResult sut = Http_FireResult_ok(response);
            (void) sut;
        }

        assert_equal(counter + 1, traits_unit_get_wrapped_signals_counter());
    }

    struct HttpResponseBuilder *responseBuilder = HttpResponseBuilder_new(&request);
    response = HttpResponseBuilder_build(&responseBuilder);

    Http_FireResult sut = Http_FireResult_ok(response);
    assert_true(Http_FireResult_isOk(sut));
    assert_false(Http_FireResult_isError(sut));
    assert_equal(Http_FireResult_unwrap(sut), response);

    {
        const size_t counter = traits_unit_get_wrapped_signals_counter();

        traits_unit_wraps(SIGABRT) {
            Error error = Http_FireResult_unwrapError(sut);
            (void) error;
        }

        assert_equal(counter + 1, traits_unit_get_wrapped_signals_counter());
    }
}

Feature(Http_FireResult_error) {
    volatile Error error = NULL;

    {
        const size_t counter = traits_unit_get_wrapped_signals_counter();

        traits_unit_wraps(SIGABRT) {
            Http_FireResult sut = Http_FireResult_error(error);
            (void) sut;
        }

        assert_equal(counter + 1, traits_unit_get_wrapped_signals_counter());
    }

    error = HttpError_NetworkingError;
    Http_FireResult sut = Http_FireResult_error(error);
    assert_false(Http_FireResult_isOk(sut));
    assert_true(Http_FireResult_isError(sut));
    assert_equal(Http_FireResult_unwrapError(sut), error);

    {
        const size_t counter = traits_unit_get_wrapped_signals_counter();

        traits_unit_wraps(SIGABRT) {
            const struct HttpResponse *response = Http_FireResult_unwrap(sut);
            (void) response;
        }

        assert_equal(counter + 1, traits_unit_get_wrapped_signals_counter());
    }
}
