//
// Created by marmelade on 30/10/22.
//

#ifndef EMBEDDEDLIBRARY_UART_RP2040_H
#define EMBEDDEDLIBRARY_UART_RP2040_H

#include "../commons/commons.h"

#include "UART.h"

#include "hardware/uart.h"

static uart_inst *hal_to_rp2040_inst(eml::hal::peripherals::UARTInstance instance) {

    return instance == eml::hal::peripherals::UART_INSTANCE0 ? uart0 : uart1;
}

namespace eml::hal::peripherals::uart {

    class UART : public interfaces::InterfaceUART, public traits::NonMovable<UART>{
    public:
        //****************************************************************
        //                   Constructors and Destructor
        //****************************************************************

        ~UART() override {

            if(isInitialised()) {

                deinit();
            }
        }

        UART(const UART &)=delete;
        UART(UART &&)=delete;

        // ****************************************************************
        //                            Operators
        // ****************************************************************
        UART &operator=(const UART &)=delete;
        UART &operator=(UART &&)=delete;

        // ****************************************************************
        //                          Static Functions
        // ****************************************************************

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

        // ****************************************************************
        //                             Functions
        // ****************************************************************

        bool init(const pin_t &rx_pin, const pin_t &tx_pin, uint baudrate) override {

            m_baudrate = uart_init(hal_to_rp2040_inst(m_instance), baudrate);
            setPins(rx_pin, tx_pin);
            setFormat(8, 1, Parity::PARITY_NONE);

            return false;
        }

        bool deinit() override {

            uart_deinit(hal_to_rp2040_inst(m_instance));

            return false;
        }

        uint8_t read() override {

            return uart_getc(hal_to_rp2040_inst(m_instance));
        }

        void read(uint8_t * const buffer, const size_t length) override {

            for(size_t i{0}; i < length; i++) {

                uart_read_blocking(hal_to_rp2040_inst(m_instance), buffer, length);
            }
        }

        void write(const uint8_t buffer) override {

            uart_putc(hal_to_rp2040_inst(m_instance), buffer);
        }

        void write(const uint8_t * const buffer, const size_t length) override {

            for(size_t i{0}; i < length; i++) {

                uart_putc(hal_to_rp2040_inst(m_instance), buffer[i]);
            }
        }

        bool setPins(const pin_t &rx_pin, const pin_t &tx_pin) override {

            m_rx_pin = rx_pin;
            m_tx_pin = tx_pin;

            gpio_set_function(m_rx_pin.pin, GPIO_FUNC_UART);
            gpio_set_function(m_tx_pin.pin, GPIO_FUNC_UART);

            return false;
        }

        uint setBaudrate(const uint baudrate) override {

            //  If initialised:
            //      set uart baudrate to m_baudrate
            //      return m_baudrate
            //  Else
            //      return m_baudrate
            return m_baudrate = isInitialised() ? uart_set_baudrate(hal_to_rp2040_inst(m_instance), baudrate) : m_baudrate;
        }

        uint getBaudrate() const override {

            return m_baudrate;
        }

        bool isInitialised() const override {

            return uart_is_enabled(hal_to_rp2040_inst(m_instance));
        }

        /**
         *  Determine how many data is waiting in the RX FIFO.
         *
         *  @warning This implementation only returns a boolean
         *
         * @return 0 if nothing waiting otherwise number of bytes waiting
         */
        size_t isReadable() const override {

            return uart_is_readable(hal_to_rp2040_inst(m_instance));
        }

        /**
         * Determine how many space is available in the TX FIFO.
         *
         * @note This implementation only returns a boolean
         *
         * @return 0 if no space available otherwise number of bytes that can be sent
         */
        size_t isWritable() const override {

            return uart_is_writable(hal_to_rp2040_inst(m_instance));
        }

        void setFormat(uint data_bits, uint stop_bits, peripherals::uart::Parity parity)  const override {

            uart_set_format(hal_to_rp2040_inst(m_instance), data_bits, stop_bits, static_cast<uart_parity_t>(parity));
        }

        void setHWFlow(bool cts, bool rts) override {

            uart_set_hw_flow(hal_to_rp2040_inst(m_instance), cts, rts);
        }

    protected:
        //****************************************************************
        //                   Constructors and Destructor
        //****************************************************************

        explicit UART(const peripherals::UARTInstance instance)
        : InterfaceUART() {

            m_instance = instance;
        }

    };

} // namespace eml::hal::peripherals::uart

#endif //EMBEDDEDLIBRARY_UART_RP2040_H
