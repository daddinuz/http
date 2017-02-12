cmake_minimum_required(VERSION 3.0)
project(http)

set(CMAKE_C_FLAGS "-std=c99 -Werror -Wall -Wextra -Wpedantic -Wuninitialized -Wmaybe-uninitialized")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
include_directories(include/http)

#####
# Dependencies
###
set(DEPENDENCY_PATH ${PROJECT_SOURCE_DIR}/deps)

set(PICOHTTP_PATH ${DEPENDENCY_PATH}/picohttpparser)
include_directories(${PICOHTTP_PATH})
add_library(picohttpparser ${PICOHTTP_PATH}/picohttpparser.h ${PICOHTTP_PATH}/picohttpparser.c)

set(STRDUP_PATH ${DEPENDENCY_PATH}/strdup)
include_directories(${STRDUP_PATH})
add_library(strdup ${STRDUP_PATH}/strdup.h ${STRDUP_PATH}/strdup.c)

#####
# Archive
###
set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
set(SOURCE_PATH ${PROJECT_SOURCE_DIR}/src)
file(GLOB HEADER_FILES ${HEADER_PATH}/*.h)
file(GLOB SOURCE_FILES ${SOURCE_PATH}/*.c)
add_library(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE curl picohttpparser strdup)

#####
# Examples
###
set(EXAMPLE_PATH ${PROJECT_SOURCE_DIR}/examples)
add_executable(example ${EXAMPLE_PATH}/example.c)
target_link_libraries(example PRIVATE ${PROJECT_NAME})
