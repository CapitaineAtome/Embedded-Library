//
// Created by marmelade on 06/11/22.
//

#ifndef EMBEDDEDLIBRARY_SPI_RP2040_H
#define EMBEDDEDLIBRARY_SPI_RP2040_H

#include "../interfaces/InterfaceSPI.h"

#include <hardware/spi.h>

static spi_inst *hal_to_rp2040_inst(hal::peripherals::SPIInstance instance) {

    return instance == hal::peripherals::SPI_INSTANCE0 ? spi0 : spi1;
}

namespace hal::peripherals::spi {

class SPI : public interfaces::InterfaceSPI {
    public:
        // ****************************************************************
        //                              Enums
        // ****************************************************************

        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************

        ~SPI() override {

            if(isInitialised()) {

                deinit();
            }
        }

        SPI(const SPI &) = delete;

        SPI(SPI &&) = delete;

        // ****************************************************************
        //                            Operators
        // ****************************************************************

        SPI &operator=(const SPI &) = delete;

        SPI &operator=(SPI &&) = delete;

        // ****************************************************************
        //                          Static Functions
        // ****************************************************************

        static SPI &getInstance(const uint8_t instance) {

            switch(instance) {
                default:
                case SPI_INSTANCE0:
                    static SPI s_spi_instance0{static_cast<const SPIInstance>(instance)};
                    return s_spi_instance0;

                case SPI_INSTANCE1:
                    static SPI s_spi_instance1{static_cast<const SPIInstance>(instance)};
                    return s_spi_instance1;
            }
        }

        // ****************************************************************
        //                             Functions
        // ****************************************************************

        bool init(const pin_t &sck_pin,
                  const pin_t &mosi_pin,
                  const pin_t &miso_pin,
                  const uint frequency) override {

            m_sck_pin = sck_pin;
            m_mosi_pin = mosi_pin;
            m_miso_pin = miso_pin;

            m_frequency = spi_init(hal_to_rp2040_inst(m_instance), frequency);

            gpio_set_function(m_sck_pin.pin, GPIO_FUNC_SPI);
            gpio_set_function(m_mosi_pin.pin, GPIO_FUNC_SPI);
            gpio_set_function(m_miso_pin.pin, GPIO_FUNC_SPI);

            m_inited = true;

            return false;
        }

        bool deinit() override {

            spi_deinit(hal_to_rp2040_inst(m_instance));

            m_inited = false;

            return false;
        }

        [[nodiscard]] bool isInitialised() const override {

            return m_inited;
        }

        void select(const uint pin) const  override {

            gpio_put(pin, false);
        }

        void deselect(const uint pin) const  override {

            gpio_put(pin, true);
        }

        bool setFormat(const uint data_bits,
                       const enum peripherals::spi::ClockPolarity clk_pol,
                       const enum peripherals::spi::ClockPhase clk_pha,
                       const BitOrder order) override {

            spi_set_format(hal_to_rp2040_inst(m_instance),
                           data_bits,
                           static_cast<spi_cpol_t>(clk_pol),
                           static_cast<spi_cpha_t>(clk_pha),
                           static_cast<spi_order_t>(order));

            return false;
        }

        bool setMode(const peripherals::Mode mode) override {

            m_mode = mode;
            spi_set_slave(hal_to_rp2040_inst(m_instance), mode == Mode::MODE_SLAVE);

            return false;
        }

        peripherals::Mode getMode() const override {

            return m_mode;
        }

        [[nodiscard]] bool isWritable() const override {

            return spi_is_writable(hal_to_rp2040_inst(m_instance));
        }
        [[nodiscard]] bool isReadable() const override {

            return spi_is_readable(hal_to_rp2040_inst(m_instance));
        }
        [[nodiscard]] bool isBusy() const override {

            return spi_is_busy(hal_to_rp2040_inst(m_instance));
        }

        int read(uint8_t * const buffer, const size_t len) override {

            return spi_read_blocking(hal_to_rp2040_inst(m_instance), 0, buffer, len);
        }

        int read(uint16_t * const buffer, const size_t len) override {

            return spi_read16_blocking(hal_to_rp2040_inst(m_instance), 0, buffer, len);
        }

        int repeated_read(uint8_t repeated_tx, uint8_t * const buffer, const size_t len) override {

            return spi_read_blocking(hal_to_rp2040_inst(m_instance), repeated_tx, buffer, len);
        }

        int repeated_read(uint16_t repeated_tx, uint16_t * const buffer, const size_t len) override {

            return spi_read16_blocking(hal_to_rp2040_inst(m_instance), repeated_tx, buffer, len);
        }

        int write(const uint8_t * const buffer, const size_t len) override {

            return spi_write_blocking(hal_to_rp2040_inst(m_instance), buffer, len);
        }

        int write(const uint16_t * const buffer, const size_t len) override {

            return spi_write16_blocking(hal_to_rp2040_inst(m_instance), buffer, len);
        }

    protected:
        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************

        explicit SPI(const SPIInstance instance) : InterfaceSPI{}, m_inited{false} {

            m_instance = instance;
        }

        bool m_inited;

    private:
    };
} // namespace hal::peripherals::spi

#endif //EMBEDDEDLIBRARY_SPI_RP2040_H
