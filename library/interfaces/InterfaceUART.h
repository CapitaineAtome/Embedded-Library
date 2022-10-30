//
// Created by marmelade on 10/10/22.
//

#ifndef EMBEDDEDLIBRARY_INTERFACEUART_H
#define EMBEDDEDLIBRARY_INTERFACEUART_H

#include <cstdlib>

#include "../traits/Singleton.h"
#include "InterfaceDigitalGPIO.h"

namespace hal::interfaces {

    class InterfaceUART : public traits::Singleton {
    public:
        //****************************************************************
        //                             Enums
        //****************************************************************



        //****************************************************************
        //                   Constructors and Destructor
        //****************************************************************

        /**
         * The destructor must call close()
         */
        ~InterfaceUART() override =default;

        //****************************************************************
        //                           Operators
        //****************************************************************



        //****************************************************************
        //                             Functions
        //****************************************************************

         /**
          * Initialise a new instance of an UART interface.
          *
          * @note Call this function before using an instance of a UART interface.
          *
          * @param rx_pin rx pin
          * @param tx_pin tx pin
          * @param baudrate value of the baud rate
          * @return whether an error occurred or not
          */
        virtual bool init(uint rx_pin, uint tx_pin, uint baudrate)=0;

        /**
         * Deinitialise an instance of the UART.
         *
         * @return whether an error occurred or not
         */
        virtual bool deinit()=0;

        /**
         * Read a byte into UART and returns it.
         *
         * @return byte read
         */
        virtual uint8_t read()=0;

        /**
         * Read into the UART and store the value into an array.
         *
         * @param buffer array of data to read
         * @param length length of the array
         */
        virtual void read(uint8_t *buffer, const size_t length)=0;

        /**
         * Send a byte through the UART
         *
         * @param buffer data to send
         */
        virtual void write(const uint8_t buffer)=0;

        /**
         * Send the data in buffer through the UART.
         *
         * @param buffer array of data do send
         * @param length length of the array
         */
        virtual void write(const uint8_t * const buffer, const size_t length)=0;

        /**
         * Set the RX et TX pin of the UART
         *
         * @param rx_pin rx pin
         * @param tx_pin tx pin
         * @return whether an error occurred
         */
        virtual bool setPins(const uint rx_pin, const uint tx_pin)=0;

        /**
         * Set the RX et TX pin of the UART
         *
         * @param rx_pin rx pin
         * @param tx_pin tx pin
         * @return whether an error occurred
         */
        virtual bool setPins(const interfaces::InterfaceDigitalGPIO &rx_pin, const interfaces::InterfaceDigitalGPIO &tx_pin) {

            return setPins(rx_pin.getPin(), tx_pin.getPin());
        }

        /**
         *  Set the value of the baud rate as close as possible to the value provided.
         *
         * @param baudrate value of the baud rate
         * @return effective value set
         */
        virtual uint setBaudrate(const uint baudrate)=0;

        /**
         * Get the baud rate value
         * @return value of the baud rate
         */
        [[nodiscard]] virtual uint getBaudrate() const=0;

        /**
         * Get the last error that occurred.
         *
         * @return last error
         */
        virtual enum Error getLastError() const {

            return m_last_error;
        }

        /**
         * Determine if the UART has been initialised
         *
         * @return true if it has been reinitialised, false otherwise
         */
        [[nodiscard]] virtual bool isInitialised()const=0;

        /**
         *  Determine whether data is waiting in the RX FIFO.
         *
         * @return true if data available, 0 otherwise
         */
        [[nodiscard]] virtual bool isReadable()const=0;

        /**
         * Determine if space is available in the TX FIFO.
         *
         * @return true if there is space, false otherwise
         */
        [[nodiscard]] virtual bool isWritable()const=0;

        /**
         * Set UART data format.
         * Configure the data format for the UART.
         *
         * @param data_bits number of bits of data 5..8
         * @param stop_bits number of stop bits 1..2
         * @param parity parity option
         */
        virtual void setFormat(uint data_bits, uint stop_bits, peripherals::uart::Parity parity) const=0;

        /**
         * Set UART flow control cts/rts.
         *
         * @param cts if true enable flow control of TX by clear-to-send input
         * @param rts if true enable assertion of request-to-send output by RX flow control
         */
        virtual void setHWFlow(bool cts, bool rts)=0;

        // InterfaceUART &getInstance(const uint8_t instance) override =0;

    protected:
        //****************************************************************
        //                   Constructors and Destructor
        //****************************************************************

        InterfaceUART()
        : m_rx_pin{0}, m_tx_pin{0}, m_baudrate{0}, m_instance{peripherals::UART_INSTANCE0}, m_last_error{Error::NONE} {}

        uint m_rx_pin;
        uint m_tx_pin;
        uint m_baudrate;

        peripherals::UARTInstance m_instance;
        enum Error m_last_error;

    private:

    };

} // hal::// interface

#endif //EMBEDDEDLIBRARY_INTERFACEUART_H
