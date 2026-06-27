cmake_minimum_required(VERSION 4.3)

project(tests)

include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest
    GIT_TAG v2.5.2
)
FetchContent_MakeAvailable(doctest)

file(GLOB_RECURSE SOURCES tests/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE doctest fsn)

