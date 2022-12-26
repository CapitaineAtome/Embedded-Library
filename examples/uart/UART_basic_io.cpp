//
// Created by marmelade on 29/11/22.
//

#include "peripherals/UART.h"
#include "peripherals/DigitalInOut.h"
#include <cstring> // for strlen

using namespace eml;

int main() {

    const char *message{"Hello, World!"};
    uint8_t msg[32]{};

    auto &uart{hal::peripherals::uart::UART::getInstance(hal::peripherals::UARTInstance::UART_INSTANCE0)};

    uart.init(hal::pin(hal::PIN::PIN1),
              hal::pin(hal::PIN::PIN0),
              hal::peripherals::UART_DEFAULT_BAUD_RATE);

    while(true) {

        if(uart.isReadable()) {

            uart.read(msg, sizeof_array(msg));
        }

        if(uart.isWritable()) {

            uart.write(reinterpret_cast<const uint8_t *const>(message), strlen(message));
        }

        hal::sleep_millis(500);

    }
}
