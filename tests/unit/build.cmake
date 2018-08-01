add_library(feature-http-fire-result ${CMAKE_CURRENT_LIST_DIR}/features/http_fire_result.h ${CMAKE_CURRENT_LIST_DIR}/features/http_fire_result.c)
target_link_libraries(feature-http-fire-result PRIVATE http traits-unit)

add_library(feature-http-maybe-text ${CMAKE_CURRENT_LIST_DIR}/features/http_maybe_text.h ${CMAKE_CURRENT_LIST_DIR}/features/http_maybe_text.c)
target_link_libraries(feature-http-maybe-text PRIVATE http traits-unit)

add_library(fixtures ${CMAKE_CURRENT_LIST_DIR}/fixtures.h ${CMAKE_CURRENT_LIST_DIR}/fixtures.c)
target_link_libraries(fixtures PRIVATE http traits-unit)

add_executable(describe ${CMAKE_CURRENT_LIST_DIR}/describe.c)
target_link_libraries(describe PRIVATE traits-unit fixtures feature-http-fire-result feature-http-maybe-text)

add_test(describe describe)
enable_testing()
