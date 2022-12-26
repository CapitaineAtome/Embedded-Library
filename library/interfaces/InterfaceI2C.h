//
// Created by marmelade on 10/10/22.
//

#ifndef EMBEDDEDLIBRARY_INTERFACEI2C_H
#define EMBEDDEDLIBRARY_INTERFACEI2C_H

#include <cstdint>

#include "../traits/Singleton.h"
#include "../commons/commons.h"

namespace eml::hal::interfaces {

    class InterfaceI2C : public traits::Singleton {
    public:
        // ****************************************************************
        //                              Enums
        // ****************************************************************

        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************
/**
         * The destructor must call @ref eml::hal::interfaces::InterfaceI2C::deinit() "deinit()" in the concrete class
         */
        ~InterfaceI2C() override =default;

        InterfaceI2C(const InterfaceI2C &)=delete;
        InterfaceI2C(InterfaceI2C &&)=delete;

        // ****************************************************************
        //                            Operators
        // ****************************************************************

        InterfaceI2C &operator=(const InterfaceI2C &)=delete;
        InterfaceI2C &operator=(InterfaceI2C &&)=delete;

        // ****************************************************************
        //                          Static Functions
        // ****************************************************************

        /**
         * Check if the address provided is a special I2C address
         *
         * @param addr address to check on
         * @return true whether or not the address provided is a special I2C address
         */
        [[nodiscard]] static bool isSpecialAddress(uint8_t addr) noexcept {

            // I2C reserves some addresses for special purposes.
            // These are any addresses of the form 000 0xxx or 111 1xxx
            return (addr & 0x78U) == 0U || (addr & 0x78U) == 0x78U;
        }

        // ****************************************************************
        //                             Functions
        // ****************************************************************

        /**
         * Initialise the I2C instance.
         *
         * @param sda_pin data pin
         * @param scl_pin clock pin
         * @param baudrate baud rate in Hz
         * @return whether the initialisation had an error
         */
        [[nodiscard]] virtual bool init(const pin_t &sda_pin, const pin_t &scl_pin, const uint baudrate)=0;

        /**
         * De initialise the I2C instance.
         *
         * @return whether the de initialisation had an error
         */
        virtual bool deinit()=0;

        /**
         * Select a register from a device given by its address.
         *
         * @param addr address of the device to talk
         * @param reg register to select
         */
        virtual void selectRegister(const uint8_t addr, const uint8_t reg) {

            write(addr, &reg, 1, true);
        }

        /**
         * Read into a device and store the data into a buffer.
         *
         * @param addr device on which to read
         * @param buffer buffer to store data
         * @param length maximum length of the buffer
         * @param nostop whether to hold the bus line
         * @return number of bytes read
         */
        virtual std::size_t read(const uint8_t addr, uint8_t *buffer, const size_t length, const bool nostop)=0;

        /**
         * Write a buffer to a device.
         *
         * @param addr device which to write
         * @param buffer buffer of datas to write
         * @param length length of the buffer
         * @param nostop whether to hold the bus line
         * @return number of bytes written
         */
        virtual std::size_t write(const uint8_t addr, const uint8_t * const buffer, const size_t length, const bool nostop)=0;

        /**
         * Read from a register from a device and store the data into a buffer.
         *
         * @param addr device on which to read
         * @param reg register to select
         * @param buffer buffer to store the data
         * @param length length of the buffer
         * @param nostop whether to hold the bus line
         * @return number of bytes read
         */
        virtual std::size_t readfrom(const uint8_t addr, const uint8_t reg, uint8_t *buffer, const size_t length, bool nostop) {

            selectRegister(addr, reg);
            return read(addr, buffer, length, nostop);
        }

        /**
         * Write buffer to a register from a device.
         *
         * @param addr device on which to write
         * @param reg register to select
         * @param buffer buffer of datas to write
         * @param length length of the buffer
         * @param nostop whether to hold the bus line
         * @return number of bytes written
         */
        virtual std::size_t writeto(const uint8_t addr, const uint8_t reg, const uint8_t * const buffer, const size_t length, bool nostop) {

            selectRegister(addr, reg);
            return write(addr, buffer, length, nostop);
        }

        /**
         * Set data and clock pins.
         *
         * @param sda_pin data pin
         * @param scl_pin clock pin
         * @return whether settings had an error
         */
        [[nodiscard]] virtual bool setPins(const pin_t &sda_pin, const pin_t &scl_pin)=0;

        /**
         * Set the data and clock pins arguments accordingly.
         *
         * @param sda_pin data pin
         * @param scl_pin clock pin
         * @return cannot fail
         */
        virtual bool getPins(pin_t &sda_pin, pin_t &scl_pin) const {

            sda_pin = m_sda_pin;
            scl_pin = m_scl_pin;

            return false;
        }

        /**
         * Set the I2C instance frequency.
         *
         * @note Frequency will be set as close as the intended value.
         *
         * @param frequency frequency on which to run the instance
         * @return frequency selected, may not be the same as the one provided
         */
        virtual uint setFrequency(const uint frequency)=0;

        /**
         * Returns the frequency in Hz on which the I2C instance run.
         *
         * @return frequency in Hz
         */
        [[nodiscard]] virtual uint getFrequency() const=0;

        /**
         * Returns whether or not the instance was initialised.
         *
         * @return true if initialised, false otherwise
         */
        [[nodiscard]] bool isInitialised() const {

            return m_inited;
        }

        /**
         * Whether there is data to read on the instance.
         *
         * @return number of bytes to read
         */
        [[nodiscard]] virtual std::size_t isReadable()=0;

        /**
         * Whether we can write on the instance.
         *
         * @return number of bytes writable
         */
        [[nodiscard]] virtual std::size_t isWritable()=0;

        /**
         * Set the device mode.
         *
         * @param addr device to set
         * @param mode device mode
         */
        virtual void setMode(const uint8_t addr, const peripherals::Mode mode)=0;

        // ----------------------------------------------------------------

        /**
         * Scan a range of address [start; stop] and store it on buffer if there is a device listening at this address.
         *
         * @param buffer list that will hold the adresses of the available peripherals
         * @param length length of the list
         * @param start address to start scan
         * @param stop address to stop scanning
         */
        void scan(uint8_t *buffer, uint8_t length, uint8_t start, uint8_t stop) {

            // Dummy data
            uint8_t rx_data;

            for(uint8_t addr = start; addr <= stop && addr < length && addr < (1U << 7U); addr++) {

                // Skip reserved address
                if(isSpecialAddress(addr)) {
                    continue;
                }

                // Send dummy data and check for a response
                buffer[addr] = (read(addr, &rx_data, 1, false) >= 0) ? addr : 0x00U;
            }
        }

        friend void swap(InterfaceI2C &first, InterfaceI2C &second) {

            using std::swap;

            swap(first.m_sda_pin, second.m_sda_pin);
            swap(first.m_scl_pin, second.m_scl_pin);
            swap(first.m_frequency, second.m_frequency);
            swap(first.m_instance, second.m_instance);
            swap(first.m_inited, second.m_inited);
        }

    protected:
        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************

        InterfaceI2C()
        : m_sda_pin{}, m_scl_pin{}, m_frequency{}, m_instance{}, m_inited{} {}

        pin_t m_sda_pin{}; ///< Hold the sda pin
        pin_t m_scl_pin{}; ///< Hold the scl pin

        uint m_frequency{}; ///< Hold the frequency at which the clock will run at

        peripherals::I2CInstance m_instance; ///< Hold the instance of the current I2C interface

        bool m_inited;

    private:
    };

} // eml::hal::interface

#endif //EMBEDDEDLIBRARY_INTERFACEI2C_H
