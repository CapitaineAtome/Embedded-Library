//
// Created by marmelade on 27/12/22.
//

#include "devices/SSD1306.h"

[[noreturn]] int main() {

    auto &i2c_instance{eml::hal::peripherals::i2c::I2C::getInstance(eml::hal::peripherals::I2CInstance::I2C_INSTANCE0)};

    i2c_instance.init(eml::hal::pin(eml::hal::PIN::PIN_I2C_SDA), eml::hal::pin(eml::hal::PIN::PIN_I2C_SCL), eml::hal::peripherals::I2C_DEFAULT_BAUD_RATE);

    auto screen_oled{eml::hal::devices::SSD1306(i2c_instance)};

    screen_oled.init();

    while (true) {
        eml::hal::sleep_millis(50);
    }

}
