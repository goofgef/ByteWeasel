cmake_minimum_required(VERSION 3.26)
project(zagmate C)

set(CMAKE_C_STANDARD 11)

include_directories(headers)

file(GLOB SOURCES "src/*.c")
add_executable(zagmate ${SOURCES})