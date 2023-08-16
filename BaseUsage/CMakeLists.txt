# Base class usage example
cmake_minimum_required(VERSION 3.16)

set(PROJECT "base-usage")
project(${PROJECT} LANGUAGES C)

add_subdirectory("../." ${CMAKE_CURRENT_BINARY_DIR}/oop-c-scheme)

add_executable(${PROJECT} "main.c")
target_link_libraries(${PROJECT} oop-c-scheme)
