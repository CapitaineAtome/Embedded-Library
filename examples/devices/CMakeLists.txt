add_executable(OLED_SSD1306
        ssd1306.cpp
        )

target_link_libraries(OLED_SSD1306
        pico_stdlib
        hardware_gpio
        hardware_i2c
        )

pico_add_extra_outputs(OLED_SSD1306)

pico_enable_stdio_usb(OLED_SSD1306 1)
pico_enable_stdio_uart(OLED_SSD1306 0)