cmake_minimum_required(VERSION 3.23)

set(HARDWARE_LIB_NAME Library)
set(IMPLEMENTATION_RP2040 Implementation_RP2040)

set(PROJECT_NAME "EmbeddedLibrary")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

if(PICO_CYW43_SUPPORTED)
    message(WIFI SUPPORTED)
else()
    message(WIFI NOT SUPPORTED)
endif()

pico_sdk_init()

# include_directories(PRIVATE ../../library)
#
# file(GLOB_RECURSE HDR_FILES
#         "commons/*.h"
#         "commons/*.hpp"
#         "data_structures/*.h"
#         "data_structures/*.hpp"
#         "devices/*.h"
#         "devices/*.hpp"
#         "peripherals/*.h"
#         "peripherals/*.hpp"
#         )
#
# file(GLOB_RECURSE SRC_C_FILES
#         "commons/*.c"
#         "data_structures/*.c"
#         "devices/*.c"
#         "peripherals/*.c"
#         )
#
# file(GLOB_RECURSE SRC_CXX_FILES
#         "commons/*.cpp"
#         "data_structures/*.cpp"
#         "devices/*.cpp"
#         "peripherals/*.cpp"
#         )
#
# message("HDR files : ${HDR_FILES}")
# message("C   files : ${SRC_C_FILES}")
# message("CXX files : ${SRC_CXX_FILES}")
# message("----------------------------------------------------------------")

# set_source_files_properties(
#         ${SRC_C_FILES}
#         ${HDR_FILES}
#         PROPERTIES
#         COMPILE_FLAGS
#         "${C_BASE_FLAGS}"
# )
#
# set_source_files_properties(
#         ${SRC_CXX_FILES}
#         ${HDR_FILES}
#         PROPERTIES
#         COMPILE_FLAGS
#         "${CXX_BASE_FLAGS}"
# )

# Create the library
# add_library(${HARDWARE_LIB_NAME} INTERFACE
#         traits/NonCopyable.h
#         traits/NonMovable.h
#         traits/Singleton.h
#         commons/commons.h
#         peripherals/DigitalInOut.h
#         interfaces/InterfaceDigitalGPIO.h
#         interfaces/InterfaceUART.h
#         interfaces/InterfaceI2C.h
#         peripherals/UART.h
#         peripherals/I2C.h
#         peripherals/SPI.h
#         interfaces/InterfaceSPI.h
#         interfaces/InterfacePWM.h
#         peripherals/PWM.h
#         )

# add_library(${IMPLEMENTATION_RP2040} INTERFACE
#         traits/NonCopyable.h
#         traits/NonMovable.h
#         traits/Singleton.h
#         commons/commons.h
#         peripherals/DigitalInOut.h
#         interfaces/InterfaceDigitalGPIO.h
#         interfaces/InterfaceUART.h
#         interfaces/InterfaceI2C.h
#         peripherals/UART.h
#         peripherals/I2C.h
#         peripherals/PWM.h
#         )
#
# target_link_libraries(${IMPLEMENTATION_RP2040}
#         pico_stdlib
#         hardware_gpio
#         hardware_uart
#         hardware_i2c
#         hardware_spi
#         hardware_pwm
#         hardware_watchdog
#         )
# pico_cyw43_arch_lwip_threadsafe_background
# pico_add_extra_outputs(${IMPLEMENTATION_RP2040})
# pico_enable_stdio_uart(${IMPLEMENTATION_RP2040} 1)
# pico_enable_stdio_uart(${IMPLEMENTATION_RP2040} 0)

add_executable(Dummy_Executable
        main.cpp
        )

target_link_libraries(Dummy_Executable
        pico_stdlib
        hardware_gpio
        hardware_uart
        hardware_i2c
        hardware_spi
        hardware_pwm
        hardware_watchdog)

pico_add_extra_outputs(Dummy_Executable)

pico_enable_stdio_uart(Dummy_Executable 1)
pico_enable_stdio_usb(Dummy_Executable 0)