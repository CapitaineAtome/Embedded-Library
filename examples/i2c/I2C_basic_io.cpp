//
// Created by marmelade on 30/11/22.
//

#include "peripherals/I2C.h"

using namespace eml;

int main() {

    auto &i2c{hal::peripherals::i2c::I2C::getInstance(0)};

    i2c.init(hal::pin(8), hal::pin(9), hal::peripherals::I2C_DEFAULT_BAUD_RATE);

    while(true) {

    }

    return 0;
}
