add_library(atom ${CMAKE_CURRENT_LIST_DIR}/atom.h ${CMAKE_CURRENT_LIST_DIR}/atom.c)
target_link_libraries(atom PRIVATE alligator)
