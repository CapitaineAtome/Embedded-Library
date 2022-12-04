/**
 *
 */

#ifndef EMBEDDEDLIBRARY_COMMONS_RP2040_H
#define EMBEDDEDLIBRARY_COMMONS_RP2040_H

#include "pico/types.h"
#include "pico/time.h"

#include "hardware/gpio.h"

namespace hal {

    namespace peripherals {

        /**
         * Number of instance for the UART peripheral on a RP2040.
         */
        enum UARTInstance : uint8_t {

            UART_INSTANCE0,
            UART_INSTANCE1
        };

        /**
         * Number of instance for the SPI peripheral on a RP2040.
         */
        enum SPIInstance : uint8_t {

            SPI_INSTANCE0,
            SPI_INSTANCE1
        };

        /**
         * Number of instance for the I2C peripheral on a RP2040.
         */
        enum I2CInstance : uint8_t {

            I2C_INSTANCE0,
            I2C_INSTANCE1
        };

    } // namespace peripherals

    /**
     * Enumerate all the pin number available on a RP2040.
     */
    enum PIN : uint {

        GPIO0 = 0,
        GPIO1 = 1,
        GPIO2 = 2,
        GPIO3 = 3,
        GPIO4 = 4,
        GPIO5 = 5,
        GPIO6 = 6,
        GPIO7 = 7,
        GPIO8 = 8,
        GPIO9 = 9,

        GPIO10 = 10,
        GPIO11 = 11,
        GPIO12 = 12,
        GPIO13 = 13,
        GPIO14 = 14,
        GPIO15 = 15,
        GPIO16 = 16,
        GPIO17 = 17,
        GPIO18 = 18,
        GPIO19 = 19,

        GPIO20 = 20,
        GPIO21 = 21,
        GPIO22 = 22,
        GPIO23 = 23,
        GPIO24 = 24,
        GPIO25 = 25,
        GPIO26 = 26,
        GPIO27 = 27,
        GPIO28 = 28,
        GPIO29 = 29,

        NUMBER_GPIO_PIN,
    };

    /**
     * Structure that define how a pin is represented.
     * On the RP2040, only the pin number is needed.
     *
     * @note the value shouldn't be superior than 29. This is the pin highest number on a RP2040.
     */
    typedef struct {

        ///< The pin number
        uint pin;

    } pin_t;


    /**
     * Create and returns a pin_t struct using the argument provided.
     *
     * @param pin pin number
     * @return a pin_t structure to be used
     */
    pin_t pin(const uint pin) {

        pin_t pin_{.pin = pin};

        return pin_;
    }

    void sleep_micros(uint64_t us) {

        sleep_us(us);
    }

    void sleep_millis(uint32_t ms) {

        sleep_ms(ms);
    }

} // namespace hal

#endif //EMBEDDEDLIBRARY_COMMONS_RP2040_H