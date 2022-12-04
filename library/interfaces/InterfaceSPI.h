//
// Created by marmelade on 06/11/22.
//

#ifndef EMBEDDEDLIBRARY_INTERFACESPI_H
#define EMBEDDEDLIBRARY_INTERFACESPI_H

#include <cstdint>

#include "../traits/Singleton.h"
#include "../commons/commons.h"

namespace hal::interfaces {

    class InterfaceSPI : public traits::Singleton {
    public:
        // ****************************************************************
        //                              Enums
        // ****************************************************************

        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************
/**
         * The destructor must call @ref hal::interfaces::InterfaceSPI::deinit() "deinit()" in the concrete class
         */
        ~InterfaceSPI() override = default;

        InterfaceSPI(const InterfaceSPI &) = delete;

        InterfaceSPI(InterfaceSPI &&) = delete;

        // ****************************************************************
        //                            Operators
        // ****************************************************************

        InterfaceSPI &operator=(const InterfaceSPI &) = delete;

        InterfaceSPI &operator=(InterfaceSPI &&) = delete;

        // ****************************************************************
        //                          Static Functions
        // ****************************************************************

        // ****************************************************************
        //                             Functions
        // ****************************************************************

        /**
         *
         * @param sck_pin
         * @param mosi_pin
         * @param miso_pin
         * @param frequency
         * @return
         */
        virtual bool init(const pin_t &sck_pin,
                          const pin_t &mosi_pin,
                          const pin_t &miso_pin,
                          const uint frequency)=0;

        /**
         *
         * @return
         */
        virtual bool deinit()=0;

        /**
         *
         * @return
         */
        virtual bool isInitialised() const =0;

        /**
         *
         * @param pin
         */
        virtual void select(const uint pin) const =0;

        virtual void deselect(const uint pin) const =0;

        virtual bool setFormat(const uint data_bits,
                               const enum peripherals::spi::ClockPolarity clk_pol,
                               const enum peripherals::spi::ClockPhase clk_pha,
                               const BitOrder order)=0;

        virtual bool setMode(const peripherals::Mode mode)=0;

        virtual peripherals::Mode getMode() const =0;

        virtual bool isWritable() const=0;
        virtual bool isReadable() const=0;
        virtual bool isBusy() const=0;

        virtual int read(uint8_t * const buffer, const size_t len)=0;
        virtual int read(uint16_t * const buffer, const size_t len)=0;

        virtual int repeated_read(uint8_t repeated_tx, uint8_t * const buffer, const size_t len)=0;
        virtual int repeated_read(uint16_t repeated_tx, uint16_t * const buffer, const size_t len)=0;

        virtual int write(const uint8_t * const buffer, const size_t len)=0;
        virtual int write(const uint16_t * const buffer, const size_t len)=0;

    protected:
        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************

        InterfaceSPI()
        : m_sck_pin{0}, m_mosi_pin{0}, m_miso_pin{0}, m_frequency{0}, m_mode{}, m_instance{} {}

        pin_t m_sck_pin;
        pin_t m_mosi_pin;
        pin_t m_miso_pin;

        uint m_frequency;

        peripherals::Mode m_mode;
        peripherals::SPIInstance m_instance;

    private:
    };
} // namespace hal::interfaces

#endif //EMBEDDEDLIBRARY_INTERFACESPI_H
