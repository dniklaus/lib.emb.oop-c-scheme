cmake_minimum_required(VERSION 3.16)
set(PROJECT "oop-c-scheme")
project(${PROJECT} VERSION 1.0.0 LANGUAGES C)

# Names of needed components
set(TARGET ${PROJECT})
set(INCLUDE_DIRECTORIES ".")
set(SOURCES
	"base.c"
	"derived.c"
)

# Make the library
add_library(${TARGET} OBJECT ${SOURCES})
target_link_libraries(${TARGET})
target_include_directories(${TARGET} PUBLIC ${INCLUDE_DIRECTORIES})
