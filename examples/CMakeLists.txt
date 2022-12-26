cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME "Examples")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

pico_sdk_init()

include_directories(PRIVATE ../library)

add_subdirectory(gpio)
add_subdirectory(hello_world)
add_subdirectory(uart)
add_subdirectory(i2c)
add_subdirectory(misc)
