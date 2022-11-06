//
// Created by marmelade on 17/10/22.
//

#ifndef EMBEDDEDLIBRARY_DIGITALOUTPUT_RP2040_H
#define EMBEDDEDLIBRARY_DIGITALOUTPUT_RP2040_H

#include "../commons/commons.h"
#include "../interfaces/InterfaceDigitalGPIO.h"

#include <hardware/gpio.h>

namespace hal::peripherals::gpio {

    class DigitalInOut : public hal::interfaces::InterfaceDigitalGPIO {
    public:

        //****************************************************************
        //                   Constructors and Destructor
        //****************************************************************

        explicit DigitalInOut(uint gpio_pin) : hal::interfaces::InterfaceDigitalGPIO(gpio_pin, Direction::OUT) {

            m_gpio_func = gpio::Function::GPIO;

            // Do not call a virtual member function in constructor or destructor unless it is implemented in the class
            init();
        }

        DigitalInOut(DigitalInOut &&other) noexcept {

            if(this != &other) {

                m_gpio_pin = other.m_gpio_pin;
                m_gpio_dir = other.m_gpio_dir;
                m_gpio_pull = other.m_gpio_pull;
                m_gpio_func = other.m_gpio_func;
                m_gpio_irq = other.m_gpio_irq;
            }
        }

        ~DigitalInOut() override {

            // Do not call a virtual member function in constructor or destructor unless it is implemented in the class
            deinit();
        };

        //****************************************************************
        //                           Operators
        //****************************************************************

        DigitalInOut &operator=(DigitalInOut &&other) noexcept {

            if(this != &other) {

                m_gpio_pin = other.m_gpio_pin;
                m_gpio_dir = other.m_gpio_dir;
                m_gpio_pull = other.m_gpio_pull;
                m_gpio_func = other.m_gpio_func;
                m_gpio_irq = other.m_gpio_irq;
            }

            return *this;
        }

        // ****************************************************************
        //                             Functions
        // ****************************************************************

        void init() override {

            if( !inited() ) {
                gpio_init(m_gpio_pin);
            }
        }

        void deinit() override {

            gpio_deinit(m_gpio_pin);
            m_gpio_func = Function::NONE;
        }

        uint8_t read() override {

            return gpio_get(m_gpio_pin);
        }

        void write(const uint8_t value) override {
            return gpio_put(m_gpio_pin, value);
        }

        bool setDirection(const enum Direction gpio_dir) override {
            gpio_set_dir(m_gpio_pin, gpio_dir == Direction::OUT);

            return false;
        }

        bool setPull(const enum Pull gpio_pull) override {

            gpio_set_pulls(m_gpio_pin,
                           gpio_pull == Pull::UP,
                           gpio_pull == Pull::DOWN);

            return false;
        }

        bool setFunction(const enum Function gpio_func) override {
            gpio_function func_;

            switch(gpio_func) {
                case Function::NONE:
                    func_ = GPIO_FUNC_NULL;
                    break;
                case Function::GPIO:
                    func_ = GPIO_FUNC_SIO;
                    break;
                case Function::UART:
                    func_ = GPIO_FUNC_UART;
                    break;
                case Function::SPI:
                    func_ = GPIO_FUNC_SPI;
                    break;
                case Function::I2C:
                    func_ = GPIO_FUNC_I2C;
                    break;
                case Function::PWM:
                    func_ = GPIO_FUNC_PWM;
                    break;
                case Function::USB:
                    func_ = GPIO_FUNC_USB;
                    break;

                default:
                    hal::errno = Error::NOTAVAILABLEONPLATFORM;
                    return true;
                    break;
            }

            gpio_set_function(m_gpio_pin, func_);

            return false;
        }

    protected:

    private:

    };

} // hal::peripherals

#endif //EMBEDDEDLIBRARY_DIGITALOUTPUT_RP2040_H
