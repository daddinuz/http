add_library(http
        ${CMAKE_CURRENT_LIST_DIR}/http.h ${CMAKE_CURRENT_LIST_DIR}/http.c
        ${CMAKE_CURRENT_LIST_DIR}/http_error.h ${CMAKE_CURRENT_LIST_DIR}/http_error.c
        ${CMAKE_CURRENT_LIST_DIR}/http_fire_result.h ${CMAKE_CURRENT_LIST_DIR}/http_fire_result.c
        ${CMAKE_CURRENT_LIST_DIR}/http_maybe_text.h ${CMAKE_CURRENT_LIST_DIR}/http_maybe_text.c
        ${CMAKE_CURRENT_LIST_DIR}/http_method.h ${CMAKE_CURRENT_LIST_DIR}/http_method.c
        ${CMAKE_CURRENT_LIST_DIR}/http_request.h ${CMAKE_CURRENT_LIST_DIR}/http_request.c
        ${CMAKE_CURRENT_LIST_DIR}/http_response.h ${CMAKE_CURRENT_LIST_DIR}/http_response.c
        ${CMAKE_CURRENT_LIST_DIR}/http_status.h ${CMAKE_CURRENT_LIST_DIR}/http_status.c)
target_link_libraries(http PRIVATE curl atom text error panic option alligator)
