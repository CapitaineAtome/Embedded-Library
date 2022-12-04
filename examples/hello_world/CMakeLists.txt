add_executable(Hello_USB
        hello_usb.cpp
        )

target_link_libraries(Hello_USB
        pico_stdlib
        )

pico_add_extra_outputs(Hello_USB)

pico_enable_stdio_usb(Hello_USB 1)
pico_enable_stdio_uart(Hello_USB 0)

# -----------------------------------

add_executable(Hello_UART
        hello_uart.cpp
        )

target_link_libraries(Hello_UART
        pico_stdlib
        )

pico_add_extra_outputs(Hello_UART)

pico_enable_stdio_usb(Hello_UART 0)
pico_enable_stdio_uart(Hello_UART 1)