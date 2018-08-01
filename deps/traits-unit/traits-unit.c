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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "traits-unit.h"

/*
 * Internal macro to disable compiler tricks on unsupported platforms
 */
#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

/*
 * Some constants
 */
#define TRAITS_UNIT_OUTPUT_STREAM                       stdout
#define TRAITS_UNIT_BUFFER_CAPACITY                     1024
#define TRAITS_UNIT_INDENTATION_STEP                    2
#define TRAITS_UNIT_INDENTATION_START                   0

/*
 * Forward declare traits subject (this should come from the test file Describe macro)
 */
extern traits_unit_subject_t traits_unit_subject;

/*
 * Define private global variables
 */
jmp_buf __traits_unit_jump_buffer;

/*
 * Define internal global variables
 */
static int global_signal_id = 0;
static int global_wrapping_attempts = 0;
static void (*global_previous_signal_handler)(int) = NULL;
static volatile sig_atomic_t global_wrapped_signals_counter = 0;

static void *global_context = NULL;
static bool global_context_initialized = false;
static traits_unit_feature_t *global_feature = NULL;

/*
 * Define internal types
 */
typedef struct traits_unit_buffer_t {
    size_t _index;
    size_t _capacity;
    char *_content;
} traits_unit_buffer_t;

typedef struct traits_unit_trait_result_t {
    size_t succeed;
    size_t skipped;
    size_t failed;
    size_t todo;
    size_t all;
} traits_unit_trait_result_t;

typedef enum traits_unit_feature_result_t {
    TRAITS_UNIT_FEATURE_RESULT_SUCCEED,
    TRAITS_UNIT_FEATURE_RESULT_SKIPPED,
    TRAITS_UNIT_FEATURE_RESULT_FAILED,
    TRAITS_UNIT_FEATURE_RESULT_TODO,
} traits_unit_feature_result_t;

/*
 * Declare internal functions
 */
static void *
traits_unit_shared_malloc(size_t size);

static void
traits_unit_shared_free(void *address, size_t size);

static traits_unit_buffer_t *
traits_unit_buffer_new(size_t capacity);

static void
traits_unit_buffer_read(traits_unit_buffer_t *buffer, int fd);

static char *
traits_unit_buffer_get(traits_unit_buffer_t *buffer);

static void
traits_unit_buffer_clear(traits_unit_buffer_t *buffer);

static void
traits_unit_buffer_delete(traits_unit_buffer_t **buffer);

static void
_traits_unit_panic(size_t line, const char *file, const char *fmt, ...)
__attribute__((__noreturn__, __format__(__printf__, 3, 4)));

static void
traits_unit_print(size_t indentation_level, const char *fmt, ...)
__attribute__((__format__(__printf__, 2, 3)));

static void
traits_unit_teardown(void);

static void
traits_unit_register_teardown_on_exit(void);

static traits_unit_trait_result_t
traits_unit_run_trait(size_t indentation_level, traits_unit_trait_t *trait, traits_unit_buffer_t *buffer);

static int
traits_unit_fork_and_run_feature(traits_unit_feature_t *feature, traits_unit_buffer_t *buffer);

static traits_unit_feature_result_t
traits_unit_run_feature(size_t indentation_level, traits_unit_feature_t *feature, traits_unit_buffer_t *buffer);

static void
traits_unit_report(size_t indentation_level, size_t succeed, size_t skipped, size_t failed, size_t todo, size_t all);

static void
traits_unit_signal_handler(int signal_id);

/*
 * Define internal macros
 */
#define traits_unit_panic(fmt, ...)     _traits_unit_panic(__LINE__, __FILE__, fmt, __VA_ARGS__)
#define traits_unit_newline()           traits_unit_print(0, "\n")

/*
 * Define public functions
 */
const char *
traits_unit_version(void) {
    return (TRAITS_UNIT_VERSION_IS_RELEASE || sizeof(TRAITS_UNIT_VERSION_SUFFIX) <= 1)
           ?
           __TRAITS_UNIT_TO_STRING(TRAITS_UNIT_VERSION_MAJOR) "."
           __TRAITS_UNIT_TO_STRING(TRAITS_UNIT_VERSION_MINOR) "."
           __TRAITS_UNIT_TO_STRING(TRAITS_UNIT_VERSION_PATCH)
           :
           __TRAITS_UNIT_TO_STRING(TRAITS_UNIT_VERSION_MAJOR) "."
           __TRAITS_UNIT_TO_STRING(TRAITS_UNIT_VERSION_MINOR) "."
           __TRAITS_UNIT_TO_STRING(TRAITS_UNIT_VERSION_PATCH) "-"
           TRAITS_UNIT_VERSION_SUFFIX;
}

void *
traits_unit_get_context(void) {
    if (!global_context_initialized) {
        traits_unit_panic("Unexpected call to %s outside feature-cycle scope\n", __func__);
    }
    return global_context;
}

size_t
traits_unit_get_wrapped_signals_counter(void) {
    if (global_wrapped_signals_counter < 0) {
        // this should never happen
        traits_unit_panic("Unexpected wrapped signals counter value: %ld\n", (long) global_wrapped_signals_counter);
    }
    return (size_t) global_wrapped_signals_counter;
}

/*
 * Define main
 */
int
main(int argc, char *argv[]) {
    bool loaded = true;
    traits_unit_buffer_t *buffer = NULL;
    traits_unit_trait_t *traits_list[TRAITS_UNIT_MAX_TRAITS] = {0};
    size_t counter_succeed = 0, counter_skipped = 0, counter_failed = 0, counter_todo = 0, counter_all = 0;
    size_t indentation_level = TRAITS_UNIT_INDENTATION_START;

    traits_unit_print(0, "Running traits-unit version %s\n\n", traits_unit_version());

    /* Load traits_list */
    if (argc > 1) {
        /* Specific traits must be run */
        if (argc > TRAITS_UNIT_MAX_TRAITS) {
            /* Too many traits has been specified, not able to load traits_list */
            loaded = false;
            traits_unit_print(indentation_level, "Too many traits specified\n");
        } else {
            /* Search for the specified traits and load them into traits_list */
            size_t index = 0;
            traits_unit_trait_t *trait = NULL;
            for (int x = 1; x < argc; x++) {
                bool found = false;
                for (size_t y = 0; (trait = &traits_unit_subject.traits[y]) && trait->trait_name; y++) {
                    if (0 == strcmp(trait->trait_name, argv[x])) {
                        found = true;
                        traits_list[index++] = trait;
                    }
                }
                if (!found) {
                    /* No such trait found, not able to load traits_list */
                    loaded = false;
                    traits_unit_print(indentation_level, "Unknown trait: `%s`\n", argv[x]);
                    break;
                }
            }
        }
    } else {
        /* Load all traits present in traits_subject */
        for (size_t i = 0; i < TRAITS_UNIT_MAX_TRAITS; i++) {
            traits_list[i] = &traits_unit_subject.traits[i];
        }
    }

    if (loaded) {
        /* Run features of traits in traits_list */
        traits_unit_trait_t *trait = NULL;
        buffer = traits_unit_buffer_new(TRAITS_UNIT_BUFFER_CAPACITY);
        traits_unit_print(indentation_level, "Describing: %s\n", traits_unit_subject.subject);
        indentation_level += TRAITS_UNIT_INDENTATION_STEP;
        for (size_t i = 0; (trait = traits_list[i]) && trait->trait_name; i++) {
            traits_unit_trait_result_t trait_result = traits_unit_run_trait(indentation_level, trait, buffer);
            counter_succeed += trait_result.succeed;
            counter_skipped += trait_result.skipped;
            counter_failed += trait_result.failed;
            counter_todo += trait_result.todo;
            counter_all += trait_result.all;
        }
        indentation_level -= TRAITS_UNIT_INDENTATION_STEP;
        traits_unit_report(
                indentation_level, counter_succeed, counter_skipped, counter_failed, counter_todo, counter_all
        );
        traits_unit_buffer_delete(&buffer);
    }

    return (loaded && (0 == counter_failed)) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*
 * Define private functions
 */
void
__traits_unit_wraps_enter(int signal_id) {
    fflush(TRAITS_UNIT_OUTPUT_STREAM);
    global_signal_id = signal_id;
    global_wrapping_attempts = 1;
    global_previous_signal_handler = signal(global_signal_id, traits_unit_signal_handler);
}

bool
__traits_unit_wraps_is_done(void) {
    return 0 != global_wrapping_attempts--;
}

void
__traits_unit_wraps_exit(void) {
    fflush(TRAITS_UNIT_OUTPUT_STREAM);
    signal(global_signal_id, global_previous_signal_handler);
    global_previous_signal_handler = NULL;
    global_wrapping_attempts = 0;
    global_signal_id = 0;
}

Setup(__TraitsUnitDefaultSetup) {
    return NULL;
}

Teardown(__TraitsUnitDefaultTeardown) {

}

FixtureImplements(__TraitsUnitDefaultFixture, __TraitsUnitDefaultSetup, __TraitsUnitDefaultTeardown);

/*
 * Define internal functions
 */
void *
traits_unit_shared_malloc(size_t size) {
    /* Our memory will be readable and writable */
    int protection = PROT_READ | PROT_WRITE;

    /*
     * The buffer will be shared (meaning other processes can access it), but
     * anonymous (meaning third-party processes cannot obtain an address for it),
     * so only this process and its children will be able to use it.
     */
    int visibility = MAP_ANONYMOUS | MAP_SHARED;

    /* Perform memory mapping */
    void *memory = mmap(NULL, size, protection, visibility, 0, 0);
    if (!memory) {
        traits_unit_panic("%s\n", "Unable to map memory");
    }

    return memory;
}

void
traits_unit_shared_free(void *address, size_t size) {
    if (0 != munmap(address, size)) {
        traits_unit_panic("%s\n", "Unable to unmap memory");
    }
}

traits_unit_buffer_t *
traits_unit_buffer_new(size_t capacity) {
    traits_unit_buffer_t *self = traits_unit_shared_malloc(sizeof(*self));
    if (!self) {
        traits_unit_panic("%s\n", "Out of memory.");
        abort(); // not needed just to quiet analyzer
    }
    self->_content = traits_unit_shared_malloc(capacity + 1);
    if (!self->_content) {
        traits_unit_panic("%s\n", "Out of memory.");
    }
    self->_index = 0;
    self->_capacity = capacity;
    self->_content[capacity] = 0;
    return self;
}

void
traits_unit_buffer_read(traits_unit_buffer_t *buffer, int fd) {
    assert(buffer);
    FILE *stream = fdopen(fd, "r");

    /* Open fd */
    if (!stream) {
        traits_unit_panic("%s\n", "Unable to open file.");
    }

    /* Read from fd and write to buffer */
    buffer->_index += fread(
            buffer->_content + buffer->_index,
            sizeof(buffer->_content[0]),
            (buffer->_index >= buffer->_capacity) ? 0 : buffer->_capacity - buffer->_index,
            stream
    );
    buffer->_content[buffer->_index] = 0;

    /* Close the stream */
    fclose(stream);
}

char *
traits_unit_buffer_get(traits_unit_buffer_t *buffer) {
    assert(buffer);
    return buffer->_content;
}

void
traits_unit_buffer_clear(traits_unit_buffer_t *buffer) {
    assert(buffer);
    buffer->_index = 0;
    buffer->_content[0] = 0;
}

void
traits_unit_buffer_delete(traits_unit_buffer_t **buffer) {
    assert(buffer && *buffer);
    traits_unit_shared_free((*buffer)->_content, (*buffer)->_capacity + 1);
    traits_unit_shared_free(*buffer, sizeof(*buffer));
    *buffer = NULL;
}

void
_traits_unit_panic(size_t line, const char *file, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "\nAt %s:%zu\nError: %s\n", file, line, strerror(errno));
    vfprintf(stderr, fmt, args);
    fputs("", stderr);
    va_end(args);
    exit(-1);
}

void
traits_unit_print(size_t indentation_level, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(TRAITS_UNIT_OUTPUT_STREAM, "%*s", (int) indentation_level, "");
    vfprintf(TRAITS_UNIT_OUTPUT_STREAM, fmt, args);
    va_end(args);
}

void
traits_unit_teardown(void) {
    if (!global_feature) {
        traits_unit_panic("%s\n", "Unexpected error");
    }
    global_feature->fixture->teardown();
    global_context_initialized = false;
    global_context = NULL;
    global_feature = NULL;
}

void
traits_unit_register_teardown_on_exit(void) {
    atexit(traits_unit_teardown);
}

traits_unit_trait_result_t
traits_unit_run_trait(size_t indentation_level, traits_unit_trait_t *trait, traits_unit_buffer_t *buffer) {
    traits_unit_trait_result_t trait_result;
    memset(&trait_result, 0, sizeof(trait_result));
    traits_unit_feature_t *feature = NULL;
    traits_unit_print(indentation_level, "Trait: %s\n", trait->trait_name);
    indentation_level += TRAITS_UNIT_INDENTATION_STEP;
    for (size_t i = 0; (feature = &trait->features[i]) && feature->feature && feature->feature_name; i++) {
        traits_unit_feature_result_t feature_result = traits_unit_run_feature(indentation_level, feature, buffer);
        switch (feature_result) {
            case TRAITS_UNIT_FEATURE_RESULT_SUCCEED: {
                trait_result.succeed++;
                break;
            }
            case TRAITS_UNIT_FEATURE_RESULT_SKIPPED: {
                trait_result.skipped++;
                break;
            }
            case TRAITS_UNIT_FEATURE_RESULT_FAILED: {
                trait_result.failed++;
                break;
            }
            case TRAITS_UNIT_FEATURE_RESULT_TODO: {
                trait_result.todo++;
                break;
            }
            default: {
                traits_unit_panic("Unexpected traits_unit_feature_result_t value: %d\n", feature_result);
            }
        }
        trait_result.all++;
    }
    return trait_result;
}

int
traits_unit_fork_and_run_feature(traits_unit_feature_t *feature, traits_unit_buffer_t *buffer) {
    pid_t pid;
    int fd, pipe_fd[2], pid_status;

    /* Flush TRAITS_UNIT_OUTPUT_STREAM */
    fflush(TRAITS_UNIT_OUTPUT_STREAM);

    /* Open a pipe */
    if (pipe(pipe_fd) < 0) {
        traits_unit_panic("%s\n", "Unable to open pipe.");
    }

    /* Fork the process */
    if ((pid = fork()) < 0) {
        traits_unit_panic("%s\n", "Unable to fork process.");
    }

    /* We are in the child process */
    if (0 == pid) {
        /* Close read end of pipe */
        close(pipe_fd[0]);

        /* Get write end of pipe */
        fd = pipe_fd[1];

        /* Redirect STDERR to pipe*/
        dup2(fd, STDERR_FILENO);

        /* Setup globals */
        global_feature = feature;
        global_context = feature->fixture->setup();
        global_context_initialized = true;

        /* Teardown globals on exit */
        traits_unit_register_teardown_on_exit();

        /* Run feature */
        feature->feature();

        /* Close fd */
        close(fd);

        /* Exit normally */
        exit(EXIT_SUCCESS);
    }

    /* We are in the parent process */

    /* Wait for children */
    wait(&pid_status);

    /* Close write end of pipe */
    close(pipe_fd[1]);

    /* Get read end of pipe */
    fd = pipe_fd[0];

    /* Redirect the children output to the global buffer */
    traits_unit_buffer_read(buffer, fd);

    /* Close fd */
    close(fd);

    /* Flush TRAITS_UNIT_OUTPUT_STREAM */
    fflush(TRAITS_UNIT_OUTPUT_STREAM);
    return pid_status;
}

traits_unit_feature_result_t
traits_unit_run_feature(size_t indentation_level, traits_unit_feature_t *feature, traits_unit_buffer_t *buffer) {
    traits_unit_feature_result_t result;
    traits_unit_print(indentation_level, "Feature: %s... ", feature->feature_name);
    switch (feature->action) {
        case TRAITS_UNIT_ACTION_RUN: {
            traits_unit_buffer_clear(buffer);
            const int exit_status = traits_unit_fork_and_run_feature(feature, buffer);
            if (EXIT_SUCCESS == exit_status) {
                result = TRAITS_UNIT_FEATURE_RESULT_SUCCEED;
                traits_unit_print(0, "succeed\n");
            } else {
                result = TRAITS_UNIT_FEATURE_RESULT_FAILED;
                if (!WIFEXITED(exit_status)) {
                    if (WIFSIGNALED(exit_status)) {
                        traits_unit_print(
                                0, "(terminated by signal %d - %s) ",
                                WTERMSIG(exit_status), strsignal(WTERMSIG(exit_status))
                        );
                    } else {
                        traits_unit_print(0, "(terminated abnormally) ");
                    }
                }
                traits_unit_print(0, "failed\n\n%s\n", traits_unit_buffer_get(buffer));
            }
            break;
        }
        case TRAITS_UNIT_ACTION_SKIP: {
            result = TRAITS_UNIT_FEATURE_RESULT_SKIPPED;
            traits_unit_print(0, "skipped\n");
            break;
        }
        case TRAITS_UNIT_ACTION_TODO: {
            result = TRAITS_UNIT_FEATURE_RESULT_TODO;
            traits_unit_print(0, "todo\n");
            break;
        }
        default: {
            traits_unit_panic("Unexpected traits_unit_action_t value: %d\n", feature->action);
            abort();  // not needed, used to quiet analyzer
        }
    }
    return result;
}

void
traits_unit_report(size_t indentation_level, size_t succeed, size_t skipped, size_t failed, size_t todo, size_t all) {
    traits_unit_newline();
    const int width = snprintf(NULL, 0, "%zu", all);
    traits_unit_print(indentation_level, "Succeed: %*zu\n", width, succeed);
    traits_unit_print(indentation_level, "Skipped: %*zu\n", width, skipped);
    traits_unit_print(indentation_level, " Failed: %*zu\n", width, failed);
    traits_unit_print(indentation_level, "   Todo: %*zu\n", width, todo);
    traits_unit_print(indentation_level, "    All: %*zu\n", width, all);
}

void
traits_unit_signal_handler(int signal_id) {
    fflush(TRAITS_UNIT_OUTPUT_STREAM);
    if (signal_id != global_signal_id) {
        exit(-1);   // ensure we are handling the same signal
    }
    global_wrapped_signals_counter++;
    signal(signal_id, global_previous_signal_handler);
    siglongjmp(__traits_unit_jump_buffer, 1);
}
