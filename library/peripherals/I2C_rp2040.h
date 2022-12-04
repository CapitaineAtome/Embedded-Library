//
// Created by marmelade on 30/10/22.
//

#ifndef EMBEDDEDLIBRARY_I2C_RP2040_H
#define EMBEDDEDLIBRARY_I2C_RP2040_H

#include "../interfaces/InterfaceI2C.h"

#include <hardware/i2c.h>

static i2c_inst *hal_to_rp2040_inst(hal::peripherals::I2CInstance instance) {

    return instance == hal::peripherals::I2C_INSTANCE0 ? i2c0 : i2c1;
}

namespace hal::peripherals::i2c {

    class I2C : public interfaces::InterfaceI2C {
    public:
        // ****************************************************************
        //                              Enums
        // ****************************************************************

        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************

        ~I2C() override {

            if(isInitialised()) {

                deinit();
            }
        }

        I2C(const I2C &)=delete;
        I2C(I2C &&)=delete;

        // ****************************************************************
        //                            Operators
        // ****************************************************************

        I2C &operator=(const I2C &)=delete;
        I2C &operator=(I2C &&)=delete;

        // ****************************************************************
        //                          Static Functions
        // ****************************************************************

        static I2C &getInstance(const uint8_t instance) {

            switch(instance) {
                default:
                case I2C_INSTANCE0:
                    static I2C s_i2c_instance0{static_cast<const I2CInstance>(instance)};
                    return s_i2c_instance0;

                case I2C_INSTANCE1:
                    static I2C s_i2c_instance1{static_cast<const I2CInstance>(instance)};
                    return s_i2c_instance1;
            }
        }

        // ****************************************************************
        //                             Functions
        // ****************************************************************

        bool init(const pin_t &sda_pin, const pin_t &scl_pin, const uint frequency) override {

            m_frequency = i2c_init(hal_to_rp2040_inst(m_instance), frequency);
            setPins(sda_pin, scl_pin);

            m_inited = true;

            return false;
        }

        bool deinit() override {

            i2c_deinit(hal_to_rp2040_inst(m_instance));

            m_inited = false;

            return false;
        }

        std::size_t read(const uint8_t addr, uint8_t *buffer, const size_t length, const bool nostop) override {

            auto tmp_ = i2c_read_blocking(hal_to_rp2040_inst(m_instance), addr, buffer, length, nostop);

            if(tmp_ < 0) {

                if(tmp_ == PICO_ERROR_TIMEOUT) {
                    hal::error = Error::TIMEOUT;
                }
                else {
                    hal::error = Error::READ;
                }

                return 0;
            }

            return static_cast<size_t>(tmp_);
        }

        std::size_t write(const uint8_t addr, const uint8_t * const buffer, const size_t length, const bool nostop) override {

            auto tmp_ = i2c_write_blocking(hal_to_rp2040_inst(m_instance), addr, buffer, length, nostop);

            if(tmp_ < 0) {

                if(tmp_ == PICO_ERROR_TIMEOUT) {
                    hal::error = Error::TIMEOUT;
                }
                else {
                    hal::error = Error::WRITE;
                }

                tmp_ = 0;
            }

            return static_cast<size_t>(tmp_);
        }

        bool setPins(const pin_t &sda_pin, const pin_t &scl_pin) override {

            m_sda_pin = sda_pin;
            m_scl_pin = scl_pin;

            gpio_set_function(m_sda_pin.pin, GPIO_FUNC_I2C);
            gpio_set_function(m_scl_pin.pin, GPIO_FUNC_I2C);

            gpio_pull_up(m_sda_pin.pin);
            gpio_pull_up(m_scl_pin.pin);

            return false;
        }

        uint setFrequency(const uint frequency) override {

            return (m_frequency = i2c_set_baudrate(hal_to_rp2040_inst(m_instance), frequency));
        }

        uint getFrequency() const override {

            return m_frequency;
        }

        bool isInitialised() const override {

            return m_inited;
        }

        std::size_t isReadable() override {

            return i2c_get_read_available(hal_to_rp2040_inst(m_instance));
        }

        std::size_t isWritable() override{

            return i2c_get_write_available(hal_to_rp2040_inst(m_instance));
        }

        void setMode(const uint8_t addr, const peripherals::Mode mode) override {

            i2c_set_slave_mode(hal_to_rp2040_inst(m_instance), mode == Mode::MODE_SLAVE, addr);
        }

    protected:
        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************
        explicit I2C(const I2CInstance instance) : InterfaceI2C(), m_inited{false} {

            m_instance = instance;
        }

        bool m_inited;

    private:
    };

} // hal::peripherals::i2c

#endif //EMBEDDEDLIBRARY_I2C_RP2040_H
