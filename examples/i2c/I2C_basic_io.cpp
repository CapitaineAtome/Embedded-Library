//
// Created by marmelade on 30/11/22.
//

#include "peripherals/I2C.h"

using namespace eml;

[[noreturn]] int main() {

    auto &i2c{hal::peripherals::I2C::getInstance(hal::peripherals::I2CInstance::I2C_INSTANCE0)};

    i2c.init(hal::pin(hal::PIN::PIN8), hal::pin(hal::PIN::PIN9), hal::peripherals::I2C_DEFAULT_BAUD_RATE);

    while(true) {

    }

}
