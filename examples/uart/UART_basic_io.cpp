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

    auto &uart{hal::peripherals::uart::UART::getInstance(0)};

    uart.init(hal::pin(1),
              hal::pin(0),
              hal::peripherals::UART_DEFAULT_BAUD_RATE);

    while(true) {

        if(uart.isReadable()) {

            uart_read_blocking(uart0, msg, eml::sizeof_array(msg));

        }

        if(uart.isWritable()) {

            uart.write(reinterpret_cast<const uint8_t *const>(message), strlen(message));
        }

        hal::sleep_millis(500);

    }
}
