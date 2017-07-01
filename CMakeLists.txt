cmake_minimum_required(VERSION 3.1)
project(http)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-align -Wbad-function-cast")
endif ()

#####
# Archive
###
include_directories(${PROJECT_SOURCE_DIR}/include/http)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/include/http/*.h)
file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
add_library(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE curl)

#####
# External
###
include(ext/sds/sds.cmake)
include(ext/parson/parson.cmake)
include(ext/picohttpparser/picohttpparser.cmake)

#####
# Examples
###
set(EXAMPLE_PATH ${PROJECT_SOURCE_DIR}/examples)

add_executable(example ${EXAMPLE_PATH}/example.c)
target_include_directories(example PRIVATE ${PROJECT_SOURCE_DIR}/ext)
target_link_libraries(example PRIVATE ${PROJECT_NAME} sds parson picohttpparser)

add_executable(bench ${EXAMPLE_PATH}/bench.c)
target_link_libraries(bench PRIVATE ${PROJECT_NAME})
