//
// Created by marmelade on 17/10/22.
//

#ifndef EMBEDDEDLIBRARY_DIGITALOUTPUT_RP2040_H
#define EMBEDDEDLIBRARY_DIGITALOUTPUT_RP2040_H

#include "../commons/commons.h"
#include "../interfaces/InterfaceDigitalGPIO.h"

#include <hardware/gpio.h>

namespace eml::hal::peripherals {

    class DigitalInOut : public eml::hal::interfaces::InterfaceDigitalGPIO {
    public:

        //****************************************************************
        //                   Constructors and Destructor
        //****************************************************************

        DigitalInOut(pin_t gpio_pin, const gpio::Direction direction) : eml::hal::interfaces::InterfaceDigitalGPIO(gpio_pin, direction) {

            // Do not call a virtual member function in constructor or destructor unless it is implemented in the class

            (void) init();
        }

        DigitalInOut(DigitalInOut &&other) noexcept {

            swap(*this, other);
        }

        ~DigitalInOut() override {

            // Do not call a virtual member function in constructor or destructor unless it is implemented in the class
            deinit();
        };

        DigitalInOut(const DigitalInOut &)=delete;
        
        //****************************************************************
        //                           Operators
        //****************************************************************

        DigitalInOut &operator=(const DigitalInOut &)=delete;

        DigitalInOut &operator=(DigitalInOut &&other) noexcept {

            swap(*this, other);

            return *this;
        }

        // ****************************************************************
        //                             Functions
        // ****************************************************************

        [[nodiscard]] bool init() override {

            m_gpio_func = gpio::Function::GPIO;

            gpio_init(m_gpio_pin.pin);
            gpio_set_dir(m_gpio_pin.pin, m_gpio_dir == gpio::Direction::OUT);

            return false;
        }

        void deinit() override {

            gpio_deinit(m_gpio_pin.pin);
            m_gpio_func = gpio::Function::NONE;
        }

        [[nodiscard]] bool inited() const override {

            return m_gpio_func != gpio::Function::NONE;
        }

        uint8_t read() override {

            return gpio_get(m_gpio_pin.pin);
        }

        void write(const uint8_t value) override {
            return gpio_put(m_gpio_pin.pin, value);
        }

        bool setDirection(const enum gpio::Direction gpio_dir) override {
            gpio_set_dir(m_gpio_pin.pin, gpio_dir == gpio::Direction::OUT);

            return false;
        }

        bool setPull(const enum gpio::Pull gpio_pull) override {

            gpio_set_pulls(m_gpio_pin.pin,
                           gpio_pull == gpio::Pull::UP,
                           gpio_pull == gpio::Pull::DOWN);

            return false;
        }

        bool setFunction(const enum gpio::Function gpio_func) override {
            gpio_function func_;

            // change: create a constant lookup table and use it instead of switch
            switch(gpio_func) {
                case gpio::Function::NONE:
                    func_ = GPIO_FUNC_NULL;
                    break;
                case gpio::Function::GPIO:
                    func_ = GPIO_FUNC_SIO;
                    break;
                case gpio::Function::UART:
                    func_ = GPIO_FUNC_UART;
                    break;
                case gpio::Function::SPI:
                    func_ = GPIO_FUNC_SPI;
                    break;
                case gpio::Function::I2C:
                    func_ = GPIO_FUNC_I2C;
                    break;
                case gpio::Function::PWM:
                    func_ = GPIO_FUNC_PWM;
                    break;
                case gpio::Function::USB:
                    func_ = GPIO_FUNC_USB;
                    break;

                default:
                    eml::hal::error.store(Error::NOTAVAILABLEONPLATFORM);
                    return true;
            }

            gpio_set_function(m_gpio_pin.pin, func_);

            return false;
        }

    protected:

    private:

    };

} // eml::hal::peripherals

#endif //EMBEDDEDLIBRARY_DIGITALOUTPUT_RP2040_H
