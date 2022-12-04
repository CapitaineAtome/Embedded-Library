add_executable(UART_basic_io
        UART_basic_io.cpp
        )

target_link_libraries(UART_basic_io
        pico_stdlib
        hardware_gpio
        hardware_uart
        )

pico_add_extra_outputs(UART_basic_io)

pico_enable_stdio_usb(UART_basic_io 1)
pico_enable_stdio_uart(UART_basic_io 0)
