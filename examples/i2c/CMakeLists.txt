add_executable(I2C_basic_io
        I2C_basic_io.cpp
        )

target_link_libraries(I2C_basic_io
        pico_stdlib
        hardware_gpio
        hardware_i2c
        )

pico_add_extra_outputs(I2C_basic_io)

pico_enable_stdio_usb(I2C_basic_io 1)
pico_enable_stdio_uart(I2C_basic_io 0)
