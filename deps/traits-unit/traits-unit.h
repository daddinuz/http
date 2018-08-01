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

#include <stddef.h>
#include <signal.h>
#include <setjmp.h>
#include <stdbool.h>

#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

/* [public section begin] */

/*
* Versioning
*/
#define TRAITS_UNIT_VERSION_MAJOR       3
#define TRAITS_UNIT_VERSION_MINOR       0
#define TRAITS_UNIT_VERSION_PATCH       0
#define TRAITS_UNIT_VERSION_SUFFIX      ""
#define TRAITS_UNIT_VERSION_IS_RELEASE  1
#define TRAITS_UNIT_VERSION_HEX         0x030000

/*
 * Constants
 */
#define TRAITS_UNIT_MAX_TRAITS          96
#define TRAITS_UNIT_MAX_FEATURES        64

/*
 * Types
 */
typedef void *traits_unit_setup_fn(void);
typedef void traits_unit_teardown_fn(void);

typedef struct traits_unit_fixture_t {
    traits_unit_setup_fn *setup;
    traits_unit_teardown_fn *teardown;
} traits_unit_fixture_t;

typedef void traits_unit_feature_fn(void);

typedef enum traits_unit_action_t {
    TRAITS_UNIT_ACTION_RUN,
    TRAITS_UNIT_ACTION_SKIP,
    TRAITS_UNIT_ACTION_TODO
} traits_unit_action_t;

typedef struct traits_unit_feature_t {
    const char *feature_name;
    traits_unit_fixture_t *fixture;
    traits_unit_feature_fn *feature;
    traits_unit_action_t action;
} traits_unit_feature_t;

typedef struct traits_unit_trait_t {
    const char *trait_name;
    traits_unit_feature_t features[TRAITS_UNIT_MAX_FEATURES];
} traits_unit_trait_t;

typedef struct traits_unit_subject_t {
    const char *subject;
    traits_unit_trait_t traits[TRAITS_UNIT_MAX_TRAITS];
} traits_unit_subject_t;

/*
 * Functions
 */
extern const char *
traits_unit_version(void);

extern void *
traits_unit_get_context(void);

extern size_t
traits_unit_get_wrapped_signals_counter(void);

/*
 * Declare main in order to force definition by traits-unit
 */
extern int
main(int argc, char *argv[]);

/*
 * Macros
 */
#define Setup(Name)                       \
    void *__TRAITS_UNIT_SETUP_ID(Name)(void)        // NOLINT

#define Teardown(Name)                    \
    void __TRAITS_UNIT_TEARDOWN_ID(Name)(void)

#define Feature(Name)                     \
    void __TRAITS_UNIT_FEATURE_ID(Name)(void)

#define Fixture(Name)                    \
    extern traits_unit_fixture_t __TRAITS_UNIT_FIXTURE_ID(Name)

#define FixtureImplements(Name, Setup, Teardown)    \
    traits_unit_fixture_t __TRAITS_UNIT_FIXTURE_ID(Name) = {.setup=__TRAITS_UNIT_SETUP_ID(Setup), .teardown=__TRAITS_UNIT_TEARDOWN_ID(Teardown)}

#define Describe(Subject, ...)                  \
    traits_unit_subject_t traits_unit_subject = {.subject=(Subject), .traits={__VA_ARGS__}};

#define Trait(Name, ...)                        \
    {.trait_name=(Name), .features={__VA_ARGS__}}

#define Run(...)                                \
    __TRAITS_UNIT_FEATURE_RUN(__VA_ARGS__, __TraitsUnitDefaultFixture, __TraitsUnitDefaultFixture)

#define Skip(...)                               \
    __TRAITS_UNIT_FEATURE_SKIP(__VA_ARGS__, __TraitsUnitDefaultFixture, __TraitsUnitDefaultFixture)

#define Todo(...)                               \
    __TRAITS_UNIT_FEATURE_TODO(__VA_ARGS__, __TraitsUnitDefaultFixture, __TraitsUnitDefaultFixture)

/*
 * Helper macro to handle signals
 */
#define traits_unit_wraps(xSignalId)                                                    \
    for (                                                                               \
        __traits_unit_wraps_enter((xSignalId));                                         \
        !sigsetjmp(__traits_unit_jump_buffer, true) && __traits_unit_wraps_is_done();   \
        __traits_unit_wraps_exit()                                                      \
    )

/* [public section end] */

/* [private section begin] */

#define __TRAITS_UNIT_CAT_IMPL_(x, ...)      x ## __VA_ARGS__
#define __TRAITS_UNIT_CAT(x, ...)           __TRAITS_UNIT_CAT_IMPL_(x, __VA_ARGS__)

#define __TRAITS_UNIT_TO_STRING_IMPL_(x)     #x
#define __TRAITS_UNIT_TO_STRING(x)          __TRAITS_UNIT_TO_STRING_IMPL_(x)

#define __TRAITS_UNIT_SETUP_ID(Name)        __TRAITS_UNIT_CAT(traits_unit_user_setup_, Name)
#define __TRAITS_UNIT_TEARDOWN_ID(Name)     __TRAITS_UNIT_CAT(traits_unit_user_teardown_, Name)
#define __TRAITS_UNIT_FIXTURE_ID(Name)      __TRAITS_UNIT_CAT(traits_unit_user_fixture_, Name)
#define __TRAITS_UNIT_FEATURE_ID(Name)      __TRAITS_UNIT_CAT(traits_unit_user_feature_, Name)

#define __TRAITS_UNIT_FEATURE_RUN(Name, Fixture, ...)               \
    {.feature_name=__TRAITS_UNIT_TO_STRING(Name), .feature=__TRAITS_UNIT_FEATURE_ID(Name), .fixture=&__TRAITS_UNIT_FIXTURE_ID(Fixture), .action=TRAITS_UNIT_ACTION_RUN}

#define __TRAITS_UNIT_FEATURE_SKIP(Name, Fixture, ...)              \
    {.feature_name=__TRAITS_UNIT_TO_STRING(Name), .feature=__TRAITS_UNIT_FEATURE_ID(Name), .fixture=&__TRAITS_UNIT_FIXTURE_ID(Fixture), .action=TRAITS_UNIT_ACTION_SKIP}

#define __TRAITS_UNIT_FEATURE_TODO(Name, Fixture, ...)              \
    {.feature_name=__TRAITS_UNIT_TO_STRING(Name), .feature=__TRAITS_UNIT_FEATURE_ID(Name), .fixture=&__TRAITS_UNIT_FIXTURE_ID(Fixture), .action=TRAITS_UNIT_ACTION_TODO}

extern jmp_buf __traits_unit_jump_buffer;

extern void
__traits_unit_wraps_enter(int signal_id);

extern bool
__traits_unit_wraps_is_done(void);

extern void
__traits_unit_wraps_exit(void);

Fixture(__TraitsUnitDefaultFixture);

/* [private section end] */

#ifdef __cplusplus
}
#endif
