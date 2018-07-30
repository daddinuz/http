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

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <panic/panic.h>
#include <alligator/alligator.h>
#include "text.h"
#include "text_config.h"

#if TEXT_DEFAULT_CAPACITY < 32UL || TEXT_DEFAULT_CAPACITY >= SIZE_MAX
    #error
#endif

static size_t nextEven(const size_t size) {
    assert(size < SIZE_MAX);
    return size + (size % 2);
}

static size_t applyLoadFactor(const size_t size) {
    assert(size < SIZE_MAX);
    return nextEven((size_t) (size * TEXT_LOAD_FACTOR));
}

static size_t calculateNewCapacity(size_t currentCapacity, const size_t targetCapacity) {
    assert(currentCapacity < SIZE_MAX);
    assert(targetCapacity < SIZE_MAX);
    assert(currentCapacity < targetCapacity);
    while (currentCapacity < targetCapacity) {
        currentCapacity = applyLoadFactor(currentCapacity);
    }
    return currentCapacity;
}

static bool isTrimmable(char c) {
    return isspace(c) || isblank(c) || !isprint(c);
}

struct Text_Header {
    size_t capacity;
    size_t length;
    char *content;
};

Text Text_new(void) {
    return Text_withCapacity(TEXT_DEFAULT_CAPACITY);
}

Text Text_withCapacity(size_t capacity) {
    assert(capacity < SIZE_MAX);
    if (capacity < TEXT_DEFAULT_CAPACITY) {
        capacity = TEXT_DEFAULT_CAPACITY;
    }
    struct Text_Header *header = Option_unwrap(Alligator_malloc(
            sizeof(*header) + sizeof(header->content[0]) * (capacity + 1)
    ));
    header->content = (char *) (header + 1);
    header->content[header->length = 0] = 0;
    header->content[header->capacity = capacity] = 0;
    return header->content;
}

Text Text_quoted(const void *bytes, const size_t size) {
    assert(bytes);
    assert(size < SIZE_MAX);

    const char *data = bytes;
    Text text = Text_withCapacity(size + size / 3);

    text = Text_appendBytes(&text, "\"", 1);
    for (size_t i = 0; i < size; i++) {
        switch (*data) {
            case '"': {
                text = Text_appendBytes(&text, "\\\"", 2);
                break;
            }
            case '\\': {
                text = Text_appendBytes(&text, "\\\\", 2);
                break;
            }
            case '/': {
                text = Text_appendBytes(&text, "\\/", 2);
                break;
            }
            case '\b': {
                text = Text_appendBytes(&text, "\\b", 2);
                break;
            }
            case '\f': {
                text = Text_appendBytes(&text, "\\f", 2);
                break;
            }
            case '\n': {
                text = Text_appendBytes(&text, "\\n", 2);
                break;
            }
            case '\r': {
                text = Text_appendBytes(&text, "\\r", 2);
                break;
            }
            case '\t': {
                text = Text_appendBytes(&text, "\\t", 2);
                break;
            }
            default: {
                if (isprint(*data)) {
                    text = Text_appendFormat(&text, "%c", *data);
                } else {
                    text = Text_appendFormat(&text, "\\u%04hhx", *data);
                }
                break;
            }
        }
        data++;
    }
    text = Text_appendBytes(&text, "\"", 1);

    return text;
}

Text Text_format(const char *format, ...) {
    assert(format);
    va_list args;
    va_start(args, format);
    Text text = Text_vFormat(format, args);
    va_end(args);
    return text;
}

Text Text_vFormat(const char *format, va_list args) {
    assert(format);
    va_list argsCopy;
    va_copy(argsCopy, args);
    const int formattedSize = vsnprintf(NULL, 0, format, argsCopy);
    va_end(argsCopy);

    if (formattedSize < 0) {
        Panic_terminate("Unable to format string");
    }

    const size_t length = (size_t) formattedSize;
    Text text = Text_withCapacity(length);
    struct Text_Header *header = (struct Text_Header *) text - 1;

    vsnprintf(header->content, length + 1, format, args);
    header->length = length;
    return text;
}

Text Text_fromBytes(const void *const bytes, const size_t size) {
    assert(bytes);
    assert(size < SIZE_MAX);
    Text text = Text_withCapacity(size);
    struct Text_Header *header = (struct Text_Header *) text - 1;
    memcpy(text, bytes, size);
    text[header->length = size] = 0;
    return text;
}

Text Text_fromLiteral(const char *const literal) {
    assert(literal);
    return Text_fromBytes(literal, strlen(literal));
}

Text Text_duplicate(const TextView self) {
    assert(self);
    return Text_fromBytes(self, Text_length(self));
}

Text Text_overwrite(Text *ref, const TextView other) {
    assert(ref);
    assert(*ref);
    assert(other);
    return Text_overwriteWithBytes(ref, other, Text_length(other));
}

Text Text_overwriteWithFormat(Text *ref, const char *format, ...) {
    assert(ref);
    assert(*ref);
    assert(format);
    va_list args;
    va_start(args, format);
    Text text = Text_vOverwriteWithFormat(ref, format, args);
    va_end(args);
    return text;
}

Text Text_vOverwriteWithFormat(Text *ref, const char *format, va_list args) {
    assert(ref);
    assert(*ref);
    assert(format);
    va_list argsCopy;
    va_copy(argsCopy, args);
    const int formattedSize = vsnprintf(NULL, 0, format, argsCopy);
    va_end(argsCopy);

    if (formattedSize < 0) {
        Panic_terminate("Unable to format string");
    }

    const size_t newLength = (size_t) formattedSize;
    Text text = Text_expandToFit(ref, newLength);
    struct Text_Header *header = (struct Text_Header *) text - 1;

    vsnprintf(header->content, newLength + 1, format, args);
    header->length = newLength;
    return text;
}

Text Text_overwriteWithBytes(Text *ref, const void *const bytes, const size_t size) {
    assert(ref);
    assert(*ref);
    assert(bytes);
    assert(size < SIZE_MAX);
    Text text = Text_expandToFit(ref, size);
    struct Text_Header *header = (struct Text_Header *) text - 1;
    memmove(text, bytes, size);
    text[header->length = size] = 0;
    *ref = NULL;
    return text;
}

Text Text_overwriteWithLiteral(Text *ref, const char *const literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    return Text_overwriteWithBytes(ref, literal, strlen(literal));
}

Text Text_append(Text *ref, TextView other) {
    assert(ref);
    assert(*ref);
    assert(other);
    return Text_appendBytes(ref, other, Text_length(other));
}

Text Text_appendFormat(Text *const ref, const char *const format, ...) {
    assert(ref);
    assert(*ref);
    assert(format);
    va_list args;
    va_start(args, format);
    Text text = Text_vAppendFormat(ref, format, args);
    va_end(args);
    return text;
}

Text Text_vAppendFormat(Text *ref, const char *format, va_list args) {
    assert(ref);
    assert(*ref);
    assert(format);
    va_list argsCopy;
    va_copy(argsCopy, args);
    const int formattedSize = vsnprintf(NULL, 0, format, argsCopy);
    va_end(argsCopy);

    if (formattedSize < 0) {
        Panic_terminate("Unable to format string");
    }

    const size_t oldLength = Text_length(*ref), newLength = (size_t) formattedSize;
    Text text = Text_expandToFit(ref, oldLength + newLength);
    struct Text_Header *header = (struct Text_Header *) text - 1;

    vsnprintf(header->content + oldLength, newLength + 1, format, args);
    header->length += newLength;
    return text;
}

Text Text_appendBytes(Text *ref, const void *const bytes, const size_t size) {
    assert(ref);
    assert(*ref);
    assert(bytes);
    assert(size < SIZE_MAX);
    return Text_insertBytes(ref, Text_length(*ref), bytes, size);
}

Text Text_appendLiteral(Text *ref, const char *const literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    return Text_appendBytes(ref, literal, strlen(literal));
}

Text Text_insert(Text *ref, size_t index, TextView text) {
    assert(ref);
    assert(*ref);
    assert(index <= Text_length(*ref));
    assert(text);
    return Text_insertBytes(ref, index, text, Text_length(text));
}

Text Text_insertFormat(Text *ref, size_t index, const char *format, ...) {
    assert(ref);
    assert(*ref);
    assert(index <= Text_length(*ref));
    assert(format);
    va_list args;
    va_start(args, format);
    Text text = Text_vInsertFormat(ref, index, format, args);
    va_end(args);
    return text;
}

Text Text_vInsertFormat(Text *ref, size_t index, const char *format, va_list args) {
    assert(ref);
    assert(*ref);
    assert(index <= Text_length(*ref));
    assert(format);
    va_list argsCopy;
    va_copy(argsCopy, args);
    const int formattedSize = vsnprintf(NULL, 0, format, argsCopy);
    va_end(argsCopy);

    if (formattedSize < 0) {
        Panic_terminate("Unable to format string");
    }

    const size_t additional = (size_t) formattedSize;
    Text self = Text_expandToFit(ref, Text_length(*ref) + additional);
    struct Text_Header *header = (struct Text_Header *) self - 1;
    char *ptr = self + index;
    const char previous = self[index];
    memmove(ptr + additional, ptr, header->length - index);
    vsnprintf(ptr, additional + 1, format, args);
    self[index + additional] = previous;
    self[header->length += additional] = 0;
    return self;
}

Text Text_insertBytes(Text *ref, size_t index, const void *bytes, size_t size) {
    assert(ref);
    assert(*ref);
    assert(index <= Text_length(*ref));
    assert(bytes);
    assert(size < SIZE_MAX);
    Text self = Text_expandToFit(ref, Text_length(*ref) + size);
    struct Text_Header *header = (struct Text_Header *) self - 1;
    char *ptr = self + index;
    memmove(ptr + size, ptr, header->length - index);
    memmove(ptr, bytes, size);
    self[header->length += size] = 0;
    return self;
}

Text Text_insertLiteral(Text *ref, size_t index, const char *literal) {
    assert(ref);
    assert(*ref);
    assert(index <= Text_length(*ref));
    assert(literal);
    return Text_insertBytes(ref, index, literal, strlen(literal));
}

Text Text_quote(Text *ref) {
    assert(ref);
    assert(*ref);
    Text self = *ref;
    self = Text_quoted(self, Text_length(self));
    Text_delete(*ref);
    *ref = NULL;
    return self;
}

void Text_eraseRange(Text self, const size_t start, const size_t end) {
    assert(self);
    assert(start <= end);
    assert(end <= Text_length(self));
    if (start != end) {
        const size_t length = Text_length(self);
        if (length == end) {
            if (0 == start) {
                Text_clear(self);
            } else {
                struct Text_Header *header = (struct Text_Header *) self - 1;
                self[header->length -= (end - start)] = 0;
            }
        } else {
            struct Text_Header *header = (struct Text_Header *) self - 1;
            memmove(self + start, self + end, length - end);
            self[header->length -= (end - start)] = 0;
        }
    }
}

void Text_trimLeft(Text self) {     // TODO test
    assert(self);
    char *cursor = self;
    for (const char *end = cursor + Text_length(self); cursor < end && isTrimmable(*cursor); cursor++) {}
    Text_eraseRange(self, 0, cursor - self);
}

void Text_trimRight(Text self) {    // TODO test
    assert(self);
    char *cursor;
    const size_t length = Text_length(self);
    for (cursor = self + length; self < cursor && isTrimmable(*cursor); cursor--) {}
    Text_eraseRange(self, (isTrimmable(*cursor) ? cursor : cursor + 1) - self, length);
}

void Text_trim(Text self) {         // TODO test
    assert(self);
    Text_trimLeft(self);
    Text_trimRight(self);
}

void Text_lower(Text self) {
    assert(self);
    const size_t length = Text_length(self);
    for (size_t i = 0; i < length; i++) {
        self[i] = (char) tolower(self[i]);
    }
}

void Text_upper(Text self) {
    assert(self);
    const size_t length = Text_length(self);
    for (size_t i = 0; i < length; i++) {
        self[i] = (char) toupper(self[i]);
    }
}

void Text_clear(Text self) {
    assert(self);
    struct Text_Header *header = (struct Text_Header *) self - 1;
    self[header->length = 0] = 0;
}

void Text_setLength(Text self, size_t length) { // TODO test
    assert(self);
    assert(length <= Text_capacity(self));
    struct Text_Header *header = (struct Text_Header *) self - 1;
    header->length = length;
}

Text Text_expandToFit(Text *ref, size_t capacity) {
    assert(ref);
    assert(*ref);
    assert(capacity < SIZE_MAX);
    struct Text_Header *header = (struct Text_Header *) (*ref) - 1;
    if (capacity > header->capacity) {
        capacity = calculateNewCapacity(header->capacity, capacity);
        header = Option_unwrap(Alligator_realloc(
                header, sizeof(*header) + sizeof(header->content[0]) * (capacity + 1)
        ));
        header->content = (char *) (header + 1);
        header->content[header->capacity = capacity] = 0;
    }
    *ref = NULL;
    return header->content;
}

Text Text_shrinkToFit(Text *ref) {
    assert(ref);
    assert(*ref);
    struct Text_Header *header = (struct Text_Header *) (*ref) - 1;
    const size_t size = header->length;
    if (size < header->capacity) {
        header = Option_unwrap(Alligator_realloc(
                header, sizeof(*header) + sizeof(header->content[0]) * (size + 1)
        ));
        header->content = (char *) (header + 1);
        header->content[header->capacity = size] = 0;
    }
    *ref = NULL;
    return header->content;
}

char Text_get(const TextView self, const size_t index) {
    assert(self);
    if (index >= Text_length(self)) {
        Panic_terminate("Out of range");
    }
    return self[index];
}

char Text_put(Text self, const size_t index, const char c) {
    assert(self);
    if (index >= Text_length(self)) {
        Panic_terminate("Out of range");
    }
    char *p = self + index;
    const char bk = *p;
    *p = c;
    return bk;
}

size_t Text_length(const TextView self) {
    assert(self);
    struct Text_Header *header = (struct Text_Header *) self - 1;
    return header->length;
}

size_t Text_capacity(const TextView self) {
    assert(self);
    struct Text_Header *header = (struct Text_Header *) self - 1;
    return header->capacity;
}

bool Text_isEmpty(TextView self) {
    assert(self);
    return 0 == Text_length(self);
}

bool Text_equals(const TextView self, const TextView other) {
    assert(self);
    assert(other);
    const size_t length = Text_length(self);
    return length == Text_length(other) && 0 == memcmp(self, other, length);
}

void Text_delete(Text self) {
    if (self) {
        struct Text_Header *header = (struct Text_Header *) self - 1;
        Alligator_free(header);
    }
}
