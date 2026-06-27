cmake_minimum_required(VERSION 4.3)

option(BUILD_TESTS "Enable tests" ON)

project(fsn)

set(CMAKE_CXX_STANDARD 26)

add_library(fsn INTERFACE)
target_include_directories(fsn INTERFACE src)
target_compile_options(fsn INTERFACE
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
    -freflection
)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

