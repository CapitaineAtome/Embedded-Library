//
// Created by marmelade on 10/10/22.
//

#ifndef EMBEDDEDLIBRARY_INTERFACEI2C_H
#define EMBEDDEDLIBRARY_INTERFACEI2C_H

#include <cstdint>

#include "../traits/Singleton.h"
#include "../commons/commons.h"

namespace hal::interfaces {

    class InterfaceI2C : public traits::Singleton {
    public:
        // ****************************************************************
        //                              Enums
        // ****************************************************************

        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************
/**
         * The destructor must call @ref hal::interfaces::InterfaceI2C::deinit() "deinit()" in the concrete class
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

        static bool isSpecialAddress(uint8_t addr) noexcept {

            // I2C reserves some addresses for special purposes.
            // These are any addresses of the form 000 0xxx or 111 1xxx
            return (addr & 0x78U) == 0U || (addr & 0x78U) == 0x78U;
        }

        // ****************************************************************
        //                             Functions
        // ****************************************************************

        virtual bool init(const uint sda_pin, const uint scl_pin, const uint baudrate)=0;

        virtual bool deinit()=0;

        virtual void selectRegister(const uint8_t addr, const uint8_t reg) {

            write(addr, &reg, 1, true);
        }

        virtual std::size_t read(const uint8_t addr, uint8_t *cmd, const size_t length, const bool nostop)=0;

        virtual std::size_t write(const uint8_t addr, const uint8_t * const cmd, const size_t length, const bool nostop)=0;

        virtual bool setPins(const uint sda_pin, const uint scl_pin)=0;

        virtual bool getPins(uint &sda_pin, uint &scl_pin) const {

            sda_pin = m_sda_pin;
            scl_pin = m_scl_pin;

            return false;
        }

        virtual uint setFrequency(const uint frequency)=0;

        [[nodiscard]] virtual uint getBaudrate() const=0;

        [[nodiscard]] virtual bool isInitialised() const=0;

        virtual std::size_t isReadable()=0;

        virtual std::size_t isWritable()=0;

        virtual void setMode(const uint8_t addr, const peripherals::Mode mode)=0;

        // ----------------------------------------------------------------

        void scan(uint8_t *buffer, uint8_t length, uint8_t start, uint8_t stop) {
            // List that will hold the addresses of the available I2C peripherals

            // Dummy data
            uint8_t rx_data;

            for(uint8_t addr = start; addr < stop && addr < length && addr < (1U << 7U); addr++) {

                // Skip reserved address
                if(isSpecialAddress(addr)) {
                    continue;
                }

                // Send dummy data and check for a response
                buffer[addr] = (read(addr, &rx_data, 1, false) >= 0) ? addr : 0x00U;
            }
        }

    protected:
        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************

        InterfaceI2C()
        : m_sda_pin{0}, m_scl_pin{0}, m_frequency{0}, m_instance{} {}

        uint m_sda_pin{};
        uint m_scl_pin{};
        uint m_frequency{};

        peripherals::I2CInstance m_instance;

    private:
    };

} // hal::interface

#endif //EMBEDDEDLIBRARY_INTERFACEI2C_H
