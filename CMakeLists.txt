cmake_minimum_required(VERSION 3.16)
project(oop-c-scheme)

add_library(${PROJECT_NAME} STATIC base.c derived.c)
target_include_directories(${PROJECT_NAME} PUBLIC . )