cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME "Embedded-Library")

project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(library/sources)