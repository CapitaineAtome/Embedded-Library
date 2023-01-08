/**
 *
 */

#ifndef EMBEDDEDLIBRARY_COMMONS_RP2040_H
#define EMBEDDEDLIBRARY_COMMONS_RP2040_H

#include "pico/types.h"
#include "pico/time.h"

#include "hardware/gpio.h"

namespace eml::hal {

    namespace peripherals {

        /**
         * Number of instance for the UART peripheral on a RP2040.
         */
         enum class [[nodiscard]] UARTInstance : uint8_t {

            UART_INSTANCE0,
            UART_INSTANCE1
        };

        /**
         * Number of instance for the SPI peripheral on a RP2040.
         */
        enum class [[nodiscard]] SPIInstance : uint8_t {

            SPI_INSTANCE0,
            SPI_INSTANCE1
        };

        /**
         * Number of instance for the I2C peripheral on a RP2040.
         */
        enum class [[nodiscard]] I2CInstance : uint8_t {

            I2C_INSTANCE0,
            I2C_INSTANCE1
        };

    } // namespace peripherals

    /**
     * Enumerate all the pin number available on a RP2040.
     */
    enum class [[nodiscard]] PIN : uint {

        PIN0 = 0,
        PIN1 = 1,
        PIN2 = 2,
        PIN3 = 3,
        PIN4 = 4,
        PIN5 = 5,
        PIN6 = 6,
        PIN7 = 7,
        PIN8 = 8,
        PIN9 = 9,

        PIN10 = 10,
        PIN11 = 11,
        PIN12 = 12,
        PIN13 = 13,
        PIN14 = 14,
        PIN15 = 15,
        PIN16 = 16,
        PIN17 = 17,
        PIN18 = 18,
        PIN19 = 19,

        PIN20 = 20,
        PIN21 = 21,
        PIN22 = 22,
        PIN23 = 23,
        PIN24 = 24,
        PIN25 = 25,
        PIN26 = 26,
        PIN27 = 27,
        PIN28 = 28,
        PIN29 = 29,

        NUMBER_OF_PINS,

        // Default peripherals

#ifdef PICO_DEFAULT_UART_RX_PIN
        PIN_UART_RX = PICO_DEFAULT_UART_RX_PIN,
#endif // PICO_DEFAULT_UART_RX_PIN

#ifdef PICO_DEFAULT_UART_TX_PIN
        PIN_UART_TX = PICO_DEFAULT_UART_TX_PIN,
#endif // PICO_DEFAULT_UART_TX_PIN

#ifdef PICO_DEFAULT_I2C_SDA_PIN
        PIN_I2C_SDA = PICO_DEFAULT_I2C_SDA_PIN,
#endif // PICO_DEFAULT_I2C_SDA_PIN

#ifdef PICO_DEFAULT_I2C_SCL_PIN
        PIN_I2C_SCL = PICO_DEFAULT_I2C_SCL_PIN,
#endif // PICO_DEFAULT_I2C_SCL_PIN

#ifdef PICO_DEFAULT_SPI_RX_PIN
        PIN_SPI_MISO = PICO_DEFAULT_SPI_RX_PIN,
#endif // PICO_DEFAULT_SPI_RX_PIN

#ifdef PICO_DEFAULT_SPI_TX_PIN
        PIN_SPI_MOSI = PICO_DEFAULT_SPI_TX_PIN,
#endif // PICO_DEFAULT_SPI_TX_PIN

#ifdef PICO_DEFAULT_SPI_SCK_PIN
        PIN_SPI_SCK = PICO_DEFAULT_SPI_SCK_PIN,
#endif // PICO_DEFAULT_SPI_SCK_PIN

#ifdef PICO_DEFAULT_SPI_CSN_PIN
        PIN_SPI_CS = PICO_DEFAULT_SPI_CSN_PIN,
#endif // PICO_DEFAULT_SPI_CSN_PIN

#ifdef PICO_DEFAULT_LED_PIN
        PIN_LED = PICO_DEFAULT_LED_PIN,
#endif // PICO_DEFAULT_LED_PIN

    };

    /**
     * Structure that define how a pin is represented.
     * On the RP2040, only the pin number is needed.
     *
     * @note the value shouldn't be superior than @ref hal::PIN::NUMBER_GPIO_PIN . This is the pin highest number on a RP2040.
     */
    typedef struct [[nodiscard]]  {

        uint pin; ///< The pin

    } pin_t;


    /**
     * Create and returns a pin_t struct using the argument provided.
     *
     * @param pin pin number
     * @return a pin_t structure to be used
     */
    constexpr pin_t pin(const PIN pin) {

        return {.pin = static_cast<uint>(pin)};
    }

    void sleep_micros(uint64_t us) {

        sleep_us(us);
    }

    void sleep_millis(uint32_t ms) {

        sleep_ms(ms);
    }

} // namespace eml::hal

#endif //EMBEDDEDLIBRARY_COMMONS_RP2040_H