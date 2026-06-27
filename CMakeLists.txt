cmake_minimum_required(VERSION 4.3)

option(BUILD_TESTS "Enable tests" ON)

# cmake 4.3
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
    "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")

project(fsn)

set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD 26)

add_library(fsn)
file(GLOB_RECURSE MODULE_SOURCES src/*.cppm)
target_sources(fsn PUBLIC
    FILE_SET modules TYPE CXX_MODULES
    FILES ${MODULE_SOURCES}
)
target_compile_options(fsn PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wctor-dtor-privacy
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wsign-promo
    -Wfloat-equal
    -Wcast-qual
    -Wzero-as-null-pointer-constant
    -Wextra-semi
    -Wsign-conversion
    -Werror
    PUBLIC
    -freflection
)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

