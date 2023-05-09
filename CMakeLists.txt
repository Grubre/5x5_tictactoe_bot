cmake_minimum_required(VERSION 3.16)
project(tictactoebot LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME}_lib ${SOURCES})

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

add_custom_target(build_tests ALL COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target tictactoebot_tests)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${PROJECT_NAME}_lib)

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

file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

include_directories(external)

target_link_libraries(${PROJECT_NAME}_tests ${Boost_LIBRARIES} ${PROJECT_NAME}_lib)

enable_testing()
add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)
