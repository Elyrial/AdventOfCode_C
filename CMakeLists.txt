cmake_minimum_required(VERSION 3.16)
project(aoc_c C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(CURL REQUIRED)

add_executable(fetch_input
    src/fetch_main.c
    src/fetch_input.c
    src/common.c
)

target_include_directories(fetch_input PRIVATE src)
target_link_libraries(fetch_input PRIVATE CURL::libcurl)

file(GLOB_RECURSE SOLUTION_SOURCES "src/solutions/*.c")

add_executable(aoc
    src/main.c
    src/runner.c
    src/common.c
    ${SOLUTION_SOURCES}
)

target_include_directories(aoc PRIVATE src)
