cmake_minimum_required(VERSION 3.16)
project(tictactoebot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
    -Wall\
    -Wextra\
    -Wpedantic\
")

find_program(CLANG_TIDY NAMES "clang-tidy" "clang-tidy-10" "clang-tidy-11" REQUIRED)
set (CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})

add_subdirectory(src)

