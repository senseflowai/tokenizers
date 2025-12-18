cmake_minimum_required(VERSION 3.2...4.0)

set(PROJECT_NAME tokenizer-cpp)
set(LIB_NAME tokenizer-cpp)
set(LIB_VERSION_MAJOR 1)
set(LIB_VERSION_MINOR 0)
set(LIB_VERSION_PATCH 0)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_CPPLINT "cpplint;--config=CPPLINT.cfg;--verbose=0")

option(WITH_EXAMPLES "Build whit examples" ON)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
endif ()

find_program(CARGO_EXECUTABLE NAMES cargo HINTS "$ENV{HOME}/.cargo/bin")
if (NOT CARGO_EXECUTABLE)
    message(FATAL_ERROR "cargo not found")
endif ()

message(STATUS "Found cargo: ${CARGO_EXECUTABLE}")

add_custom_target(
        rust
        COMMAND CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR}/rust CARGO_OUTPUT_HEADER_DIR=${CMAKE_CURRENT_BINARY_DIR} ${CARGO_EXECUTABLE} build --release --manifest-path ${CMAKE_CURRENT_SOURCE_DIR}/Cargo.toml
)

file(GLOB SOURCES src/*.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

link_directories(${CMAKE_CURRENT_BINARY_DIR}/rust/release)

add_library(${LIB_NAME} ${SOURCES})

add_dependencies(${LIB_NAME} rust)

target_link_libraries(${LIB_NAME} tokenizers)

if (WITH_EXAMPLES)
    add_subdirectory(examples)
endif ()
