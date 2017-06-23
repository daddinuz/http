function(discover_directories OUT PATH)
    file(GLOB CHILDREN RELATIVE ${PATH} ${PATH}/*)
    set(DIRECTORY_LIST "")
    foreach (CHILD ${CHILDREN})
        if (IS_DIRECTORY ${PATH}/${CHILD})
            list(APPEND DIRECTORY_LIST ${PATH}/${CHILD})
        endif ()
    endforeach ()
    set(${OUT} "${DIRECTORY_LIST}" PARENT_SCOPE)
endfunction()

function(discover_dependencies DEPENDENCY_PATH)
    discover_directories(DEPENDENCIES ${DEPENDENCY_PATH})
    foreach (DEPENDENCY ${DEPENDENCIES})
        include_directories(${DEPENDENCY})
        file(GLOB BUILD_FILES ${DEPENDENCY}/*.cmake)
        foreach (BUILD_FILE ${BUILD_FILES})
            include(${BUILD_FILE})
        endforeach ()
    endforeach ()
endfunction()

function(discover_tests TEST_PATH)
    file(GLOB TEST_SOURCE_FILES ${TEST_PATH}/test_*.c)
    foreach (TEST_SOURCE_FILE ${TEST_SOURCE_FILES})
        get_filename_component(TARGET ${TEST_SOURCE_FILE} NAME_WE)
        add_executable(${TARGET} ${TEST_SOURCE_FILE})
        target_link_libraries(${TARGET} PRIVATE ${PROJECT_NAME})
        add_test(${TARGET} ${TARGET})
    endforeach (TEST_SOURCE_FILE)
endfunction()