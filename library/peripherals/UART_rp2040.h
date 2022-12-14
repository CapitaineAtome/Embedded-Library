//
// Created by marmelade on 30/10/22.
//

#ifndef EMBEDDEDLIBRARY_UART_RP2040_H
#define EMBEDDEDLIBRARY_UART_RP2040_H

#include "../commons/commons.h"

#include "UART.h"

#include "hardware/uart.h"

static inline uart_inst *hal_to_rp2040_inst(hal::peripherals::UARTInstance instance) {

    return instance == hal::peripherals::UART_INSTANCE0 ? uart0 : uart1;
}

namespace hal::peripherals::uart {

    class UART : public interfaces::InterfaceUART {
    public:
        //****************************************************************
        //                   Constructors and Destructor
        //****************************************************************

        UART(UART &&other) noexcept {

            if(this != &other) {
                m_rx_pin = other.m_rx_pin;
                m_tx_pin = other.m_tx_pin;
                m_baudrate = other.m_baudrate;
                m_last_error = other.m_last_error;
                m_instance = other.m_instance;

                other.m_rx_pin = 0;
                other.m_tx_pin = 0;
                other.m_baudrate = 0;
                other.m_last_error = Error::NONE;
                other.m_instance = UART_INSTANCE0;
            }

        }

        ~UART() override {

            if(isInitialised()) {

                deinit();
            }
        }

        //****************************************************************
        //                           Operators
        //****************************************************************

        UART &operator=(UART &&other) noexcept {

            if(this != &other) {
                m_rx_pin = other.m_rx_pin;
                m_tx_pin = other.m_tx_pin;
                m_baudrate = other.m_baudrate;
                m_last_error = other.m_last_error;
                m_instance = other.m_instance;

                other.m_rx_pin = 0;
                other.m_tx_pin = 0;
                other.m_baudrate = 0;
                other.m_last_error = Error::NONE;
                other.m_instance = UART_INSTANCE0;
            }

            return *this;
        }

        //****************************************************************
        //                             Functions
        //****************************************************************

        bool init(uint rx_pin, uint tx_pin, uint baudrate) override {

            m_last_error = Error::NONE;

            m_baudrate = uart_init(hal_to_rp2040_inst(m_instance), baudrate);
            setPins(rx_pin, tx_pin);
            setFormat(8, 1, Parity::PARITY_NONE);

            return m_last_error != Error::NONE;
        }

        bool deinit() override {

            uart_deinit(hal_to_rp2040_inst(m_instance));

            return m_last_error != Error::NONE;
        }

        uint8_t read() override {

            return uart_getc(hal_to_rp2040_inst(m_instance));
        }

        void read(uint8_t *buffer, const size_t length) override {

            uart_read_blocking(hal_to_rp2040_inst(m_instance), buffer, length);
        }

        void write(const uint8_t buffer) override {

            uart_putc(hal_to_rp2040_inst(m_instance), buffer);
        }

        void write(const uint8_t * const buffer, const size_t length) override {

            for(size_t i{0}; i < length; i++) {

                uart_putc(hal_to_rp2040_inst(m_instance), buffer[i]);
            }
        }

        bool setPins(const uint rx_pin, const uint tx_pin) override {

            m_last_error = Error::NONE;

            m_rx_pin = rx_pin;
            m_tx_pin = tx_pin;

            gpio_set_function(m_rx_pin, GPIO_FUNC_UART);
            gpio_set_function(m_tx_pin, GPIO_FUNC_UART);

            return m_last_error != Error::NONE;
        }

        uint setBaudrate(const uint baudrate) override {

            return m_baudrate = isInitialised() ? uart_set_baudrate(hal_to_rp2040_inst(m_instance), baudrate) : m_baudrate;
        }

        [[nodiscard]] uint getBaudrate() const override {

            return m_baudrate;
        }

        [[nodiscard]] bool isInitialised() const override {

            return uart_is_enabled(hal_to_rp2040_inst(m_instance));
        }

        [[nodiscard]] bool isReadable() const override {

            return uart_is_readable(hal_to_rp2040_inst(m_instance));
        }

        [[nodiscard]] bool isWritable() const override {

            return uart_is_writable(hal_to_rp2040_inst(m_instance));
        }

        void setFormat(uint data_bits, uint stop_bits, peripherals::uart::Parity parity)  const override {

            uart_set_format(hal_to_rp2040_inst(m_instance), data_bits, stop_bits, static_cast<uart_parity_t>(parity));
        }

        void setHWFlow(bool cts, bool rts) override {

            uart_set_hw_flow(hal_to_rp2040_inst(m_instance), cts, rts);
        }

        static UART &getInstance(const uint8_t instance) {

            switch(instance) {
                default:
                case UART_INSTANCE0:
                    static UART s_uart_instance0{static_cast<const UARTInstance>(instance)};
                    return s_uart_instance0;

                case UART_INSTANCE1:
                    static UART s_uart_instance1{static_cast<const UARTInstance>(instance)};
                    return s_uart_instance1;
            }
        }

    protected:
        //****************************************************************
        //                   Constructors and Destructor
        //****************************************************************

        explicit UART(const peripherals::UARTInstance instance)
        : InterfaceUART() {}

    };

} // namespace hal::peripherals::uart

#endif //EMBEDDEDLIBRARY_UART_RP2040_H
