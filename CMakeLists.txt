cmake_minimum_required(VERSION 3.1)
project(http)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-align -Wbad-function-cast -Wconversion")
endif ()

set(DEPENDENCY_PATH ${PROJECT_SOURCE_DIR}/deps)
set(ARCHIVE_PATH ${PROJECT_SOURCE_DIR})
set(TEST_PATH ${PROJECT_SOURCE_DIR}/test)

#####
# Archive
###
include(${PROJECT_NAME}.cmake)

#####
# Examples
###
set(EXAMPLE_PATH ${PROJECT_SOURCE_DIR}/examples)
add_executable(example ${EXAMPLE_PATH}/example.c)
target_link_libraries(example PRIVATE ${PROJECT_NAME})
