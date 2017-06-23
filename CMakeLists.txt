cmake_minimum_required(VERSION 3.1)
project(http)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-align -Wbad-function-cast -Wconversion")
endif ()

set(DEPENDENCY_PATH ${PROJECT_SOURCE_DIR}/deps)
set(EXAMPLE_PATH ${PROJECT_SOURCE_DIR}/examples)

#####
# Dependencies
###
include_directories(deps/hashmap)
include(deps/hashmap/hashmap.cmake)

#####
# Archive
###
include_directories(${PROJECT_SOURCE_DIR}/include/http)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/include/http/*.h)
file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
add_library(http ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(http PRIVATE curl hashmap)

#####
# Examples
###
add_executable(example ${EXAMPLE_PATH}/example.c)
target_link_libraries(example PRIVATE ${PROJECT_NAME})
