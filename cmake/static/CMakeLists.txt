cmake_minimum_required(VERSION 3.26)
project(zagmate C)

set(CMAKE_C_STANDARD 11)

set(ZAGMATE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../../headers)
file(GLOB LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/zagmate.c")

add_library(zagmate STATIC ${LIB_SOURCES})
target_include_directories(zagmate PUBLIC ${ZAGMATE_HEADERS})
set_target_properties(zagmate PROPERTIES OUTPUT_NAME "zagmate_static")