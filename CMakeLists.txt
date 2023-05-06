
cmake_minimum_required(VERSION 3.16)
project(tictactoebot LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCES src/*.cpp)

# Clang-tidy
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    # set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

# Cppcheck
find_program(CPPCHECK "cppcheck")
if(CPPCHECK)
    set(CPPCHECK_ARGS "--enable=all")
    add_custom_target(cppcheck
        COMMAND ${CPPCHECK}
        --project=${CMAKE_BINARY_DIR}/compile_commands.json
        ${CPPCHECK_ARGS}
        COMMENT "Running Cppcheck static analysis"
    )
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(tictactoebot ${Boost_LIBRARIES})

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wshadow
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3>
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
)

