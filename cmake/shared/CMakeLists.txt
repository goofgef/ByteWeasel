cmake_minimum_required(VERSION 3.26)
project(zagmate C)

set(CMAKE_C_STANDARD 11)

set(ZAGMATE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../../headers)
file(GLOB LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/zagmate.c")

add_library(zagmate SHARED ${LIB_SOURCES})
target_include_directories(zagmate PUBLIC ${ZAGMATE_HEADERS})

set_target_properties(zagmate PROPERTIES OUTPUT_NAME "zagmate_shared")

if(WIN32)
    set_target_properties(zagmate PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.import_libs"
    )
    add_custom_command(TARGET zagmate POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/.import_libs/libzagmate_shared.dll.a"
            "${CMAKE_BINARY_DIR}/libzagmate_shared.dll.a"
    )
    target_compile_definitions(zagmate PRIVATE ZAGMATE_EXPORTS)
else()
    set_target_properties(zagmate PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
endif()