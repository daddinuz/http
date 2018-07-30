set(ARCHIVE_NAME error)
message("${ARCHIVE_NAME}@${CMAKE_CURRENT_LIST_DIR} using: ${CMAKE_CURRENT_LIST_FILE}")

file(GLOB ARCHIVE_HEADERS ${CMAKE_CURRENT_LIST_DIR}/*.h)
file(GLOB ARCHIVE_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.c)
add_library(${ARCHIVE_NAME} ${ARCHIVE_HEADERS} ${ARCHIVE_SOURCES})
