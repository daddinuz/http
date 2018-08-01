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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

#define TEXT_VERSION_MAJOR        0
#define TEXT_VERSION_MINOR        1
#define TEXT_VERSION_PATCH        0
#define TEXT_VERSION_SUFFIX       ""
#define TEXT_VERSION_IS_RELEASE   0
#define TEXT_VERSION_HEX          0x000100

/**
 * A string library with support for complex operations on textual data
 *
 * @attention Every function in this library terminates the program in case of out of memory.
 */
typedef char *Text;
typedef const char *TextView;

/**
 * Creates an empty text using default capacity.
 *
 * @return a new text instance.
 */
extern Text Text_new(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new text with at least the given initial capacity.
 *
 * @attention capacity must be less than SIZE_MAX.
 *
 * @param capacity The initial capacity.
 * @return a new text instance.
 */
extern Text Text_withCapacity(size_t capacity)
__attribute__((__warn_unused_result__));

/**
 * Creates a new JSON compliant quoted instance of text starting from bytes.
 *
 * @attention bytes array must not be NULL.
 * @attention the size of the bytes array must be less than SIZE_MAX.
 *
 * @param bytes The sequence of bytes.
 * @param size The size of bytes.
 * @return a new text instance.
 */
extern Text Text_quoted(const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new text from a printf-like format.
 *
 * @attention format must not be NULL.
 *
 * @param format The printf-like format string.
 * @param ... The args for format.
 * @return a new text instance.
 */
extern Text Text_format(const char *format, ...)
__attribute__((__warn_unused_result__, __nonnull__(1), __format__(printf, 1, 2)));

/**
 * Creates a new text from a printf-like format, behaves like Text_format but takes a va_list.
 *
 * @attention format must not be NULL.
 *
 * @param format The printf-like format string.
 * @param args The args for format.
 * @return a new text instance.
 */
extern Text Text_vFormat(const char *format, va_list args)
__attribute__((__warn_unused_result__, __nonnull__, __format__(__printf__, 1, 0)));

/**
 * Creates a new text from the given bytes array.
 *
 * @attention bytes array must not be NULL.
 * @attention the size of the bytes array must be less than SIZE_MAX.
 *
 * @param bytes The bytes array.
 * @param size The size of the array.
 * @return a new text instance.
 */
extern Text Text_fromBytes(const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new text from the given literal.
 *
 * @attention literal must not be NULL.
 * @attention the length of the literal must be less than SIZE_MAX.
 *
 * @param literal The string literal.
 * @return a new text instance.
 */
extern Text Text_fromLiteral(const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Duplicates a text instance.
 * Note: capacity may be different between instances.
 *
 * @attention s must not be NULL.
 *
 * @param self The text instance to be duplicated.
 * @return a new text instance.
 */
extern Text Text_duplicate(TextView self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Overwrites the content of the text (expanding it's capacity if needed) with the other text.
 *
 * @attention ref and *ref must not be NULL.
 * @attention other must not be NULL.
 *
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param bytes The bytes array to write in the text.
 * @param size The size of the bytes array.
 * @return the modified text instance
 */
extern Text Text_overwrite(Text *ref, TextView other)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Overwrites the content of the text (expanding it's capacity if needed) with the formatted content.
 *
 * @attention ref and *ref must not be NULL.
 * @attention format must not be NULL.
 *
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param format The printf-like format string.
 * @param ... The args for format
 * @return the modified text instance
 */
extern Text Text_overwriteWithFormat(Text *ref, const char *format, ...)
__attribute__((__warn_unused_result__, __nonnull__(1, 2), __format__(printf, 2, 3)));

/**
 * Overwrites the content of the text (expanding it's capacity if needed) with the formatted content.
 * Behaves like Text_overwriteWithFormat but takes a va_list.
 *
 * @attention ref and *ref must not be NULL.
 * @attention format must not be NULL
 *
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param format The printf-like format string.
 * @param args The args for format.
 * @return the modified text instance
 */
extern Text Text_vOverwriteWithFormat(Text *ref, const char *format, va_list args)
__attribute__((__warn_unused_result__, __nonnull__, __format__(printf, 2, 0)));

/**
 * Overwrites the content of the text (expanding it's capacity if needed) with the given bytes array.
 *
 * @attention ref and *ref must not be NULL.
 * @attention bytes must not be NULL.
 * @attention size must be less than SIZE_MAX.
 *
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param bytes The bytes array to write in the text.
 * @param size The size of the bytes array.
 * @return the modified text instance
 */
extern Text Text_overwriteWithBytes(Text *ref, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Overwrites the content of the text (expanding it's capacity if needed) with the given literal.
 *
 * @attention ref and *ref must not be NULL.
 * @attention literal must not be NULL.
 * @attention the length of the literal must be less than SIZE_MAX.
 *
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param literal The literal to write in the text.
 * @return the modified text instance
 */
extern Text Text_overwriteWithLiteral(Text *ref, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Appends content to the text.
 *
 * @attention ref and *ref must not be NULL.
 * @attention other must not be NULL.
 *
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param other The text to be appended.
 * @return the modified text instance
 */
extern Text Text_append(Text *ref, TextView other)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Appends the formatted content to the text.
 *
 * @attention ref and *ref must not be NULL.
 * @attention format must not be NULL.
 *
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param format The printf-like format string.
 * @param ... The args for format
 * @return the modified text instance
 */
extern Text Text_appendFormat(Text *ref, const char *format, ...)
__attribute__((__warn_unused_result__, __nonnull__(1, 2), __format__(printf, 2, 3)));

/**
 * Appends the formatted content to the text.
 * Behaves like Text_appendFormat but takes a va_list.
 *
 * @attention ref and *ref must not be NULL.
 * @attention format must not be NULL
 *
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param format The printf-like format string.
 * @param args The args for format.
 * @return the modified text instance
 */
extern Text Text_vAppendFormat(Text *ref, const char *format, va_list args)
__attribute__((__warn_unused_result__, __nonnull__, __format__(printf, 2, 0)));

/**
 * Appends the bytes array to the text.
 *
 * @attention ref and *ref must not be NULL.
 * @attention bytes must not be NULL.
 * @attention size must be less than SIZE_MAX.
 *
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param bytes The bytes array to append.
 * @param size The size of the bytes array.
 * @return the modified text instance
 */
extern Text Text_appendBytes(Text *ref, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Appends the literal to the text.
 *
 * @attention ref and *ref must not be NULL.
 * @attention literal must not be NULL.
 * @attention the length of the literal must be less than SIZE_MAX.
 *
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param literal The literal to append.
 * @return the modified text instance
 */
extern Text Text_appendLiteral(Text *ref, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Insert text at the index position.
 *
 * @attention ref and *ref must not be NULL.
 * @attention index must be less or equal than the length of the text.
 * @attention text must not be NULL.
 *
 * @attention terminates execution if index is greater than the length of the text.
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param index The index position.
 * @param text The text to insert.
 * @return the modified text instance
 */
extern Text Text_insert(Text *ref, size_t index, TextView text)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Inserts a formatted string into this text.
 *
 * @attention ref and *ref must not be NULL.
 * @attention index must be less or equal than the length of the text.
 * @attention format must not be NULL.
 *
 * @attention terminates execution if index is greater than the length of the text.
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param index The index position.
 * @param format The printf-like format string.
 * @param ... The args for format.
 * @return the modified text instance
 */
extern Text Text_insertFormat(Text *ref, size_t index, const char *format, ...)
__attribute__((__warn_unused_result__, __nonnull__(1, 3), __format__(printf, 3, 4)));

/**
 * Inserts a formatted string into this text.
 * Behaves like Text_insertFormat but takes a va_list.
 *
 * @attention ref and *ref must not be NULL.
 * @attention index must be less or equal than the length of the text.
 * @attention format must not be NULL
 *
 * @attention terminates execution if index is greater than the length of the text.
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param index The index position.
 * @param format The printf-like format string.
 * @param args The args for format.
 * @return the modified text instance
 */
extern Text Text_vInsertFormat(Text *ref, size_t index, const char *format, va_list args)
__attribute__((__warn_unused_result__, __nonnull__, __format__(printf, 3, 0)));

/**
 * Insert bytes into this text at the index position.
 *
 * @attention ref and *ref must not be NULL.
 * @attention index must be less or equal than the length of the text.
 * @attention bytes must not be NULL.
 * @attention size must be less than SIZE_MAX.
 *
 * @attention terminates execution if index is greater than the length of the text.
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param index The index position.
 * @param bytes The bytes array to insert.
 * @param size The size of the bytes array.
 * @return the modified text instance
 */
extern Text Text_insertBytes(Text *ref, size_t index, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Insert literal into this text at the index position.
 *
 * @attention ref and *ref must not be NULL.
 * @attention index must be less or equal than the length of the text.
 * @attention literal must not be NULL.
 *
 * @attention terminates execution if index is greater than the length of the text.
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @param index The index position.
 * @param literal The literal to insert.
 * @return the modified text instance
 */
extern Text Text_insertLiteral(Text *ref, size_t index, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Modifies text quoting (JSON compliant) it's content.
 *
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @param ref The text instance reference.
 * @return the modified text instance
 */
extern Text Text_quote(Text *ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Erases content from this text.
 * Note: A starting index equal to the ending one will result in a no-op.
 *
 * @attention self must not be NULL.
 * @attention start must be less or equal than end.
 * @attention end must be less or equal than the length of the text.
 *
 * @attention terminates execution if range is invalid.
 *
 * @param self The text instance.
 * @param start Starting index included.
 * @param end Ending index excluded.
 */
extern void Text_eraseRange(Text self, size_t start, size_t end)
__attribute__((__nonnull__));

/**
 * Removes leading whitespace from left.
 *
 * @param self The text instance.
 */
extern void Text_trimLeft(Text self)
__attribute__((__nonnull__));

/**
 * Removes leading whitespace from right.
 *
 * @param self The text instance.
 */
extern void Text_trimRight(Text self)
__attribute__((__nonnull__));

/**
 * Removes leading whitespace from both endings.
 *
 * @param self The text instance.
 */
extern void Text_trim(Text self)
__attribute__((__nonnull__));

/**
 * To lower case.
 *
 * @param self The text instance.
 */
extern void Text_lower(Text self)
__attribute__((__nonnull__));

/**
 * To upper case.
 *
 * @param self The text instance.
 */
extern void Text_upper(Text self)
__attribute__((__nonnull__));

/**
 * Clears the content of the text without changing its capacity.
 *
 * @attention self must not be NULL.
 *
 * @param self The text instance.
 */
extern void Text_clear(Text self)
__attribute__((__nonnull__));

/**
 * Sets the length of the text.
 *
 * @attention self must not be NULL.
 * @attention length must not be greater than capacity.
 *
 * @param self The text instance.
 * @param length The new length.
 */
extern void Text_setLength(Text self, size_t length)
__attribute__((__nonnull__));

/**
 * Expands (if needed) the text to fit the requested capacity.
 *
 * @attention ref and *ref must not be NULL.
 * @attention capacity must be less than SIZE_MAX.
 *
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @return the modified text instance
 */
extern Text Text_expandToFit(Text *ref, size_t capacity)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Shrinks the capacity of the text to fit the size of its content.
 *
 * @attention ref and *ref must not be NULL.
 * @attention the reference to the text will be invalidated after this call, the new text is returned.
 *
 * @return the modified text instance
 */
extern Text Text_shrinkToFit(Text *ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Gets the character in the text at the given index.
 *
 * @attention self must not be NULL.
 * @attention terminates execution if index is greater or equals the text's length.
 */
extern char Text_get(TextView self, size_t index)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Puts the character in the text at the given index replacing the existing one.
 *
 * @attention self must not be NULL.
 * @attention terminates execution if index is greater or equals the text's length.
 *
 * @return the replaced character.
 */
extern char Text_put(Text self, size_t index, char c)
__attribute__((__nonnull__));

/**
 * Gets the size of the text.
 *
 * @attention self must not be NULL.
 *
 * @param self The text instance.
 * @return the size of the text.
 */
extern size_t Text_length(TextView self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Gets the capacity of the text.
 *
 * @attention self must not be NULL.
 *
 * @param self The text instance.
 * @return the capacity of the text.
 */
extern size_t Text_capacity(TextView self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Checks if the string is empty.
 */
extern bool Text_isEmpty(TextView self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Checks for equality.
 *
 * @attention self must not be NULL.
 * @attention other must not be NULL.
 */
extern bool Text_equals(TextView self, TextView other)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes an instance of a text.
 * If NULL nothing will be done.
 *
 * @param self The instance to be deleted.
 */
extern void Text_delete(Text self);

#ifdef __cplusplus
}
#endif
