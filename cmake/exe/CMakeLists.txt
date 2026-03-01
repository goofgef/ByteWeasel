cmake_minimum_required(VERSION 3.26)
project(zagmate C)

set(CMAKE_C_STANDARD 11)

set(ZAGMATE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../../headers)
file(GLOB EXE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/*.c")

add_executable(zagmate ${EXE_SOURCES})
target_include_directories(zagmate PRIVATE ${ZAGMATE_HEADERS})

if(WIN32)
    set_target_properties(zagmate PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
endif()