cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME "Embedded")

project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(BASE_FLAGS "-Wall -Wextra -Wpedantic -Wshadow  -Wunused  -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wno-format -Wno-unused-function -Wno-maybe-uninitialized")
set(CXX_BASE_FLAGS "${BASE_FLAGS} -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAS_DEBUG} -O0 -fno-rtti")

add_subdirectory(library)