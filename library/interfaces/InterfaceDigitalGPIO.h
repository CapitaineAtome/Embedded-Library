/**
 * @file AbstractGPIO
 */

#ifndef EMBEDDEDLIBRARY_INTERFACEDIGITALGPIO_H
#define EMBEDDEDLIBRARY_INTERFACEDIGITALGPIO_H

#include <cstdint>
#include <sys/types.h>
#include <utility>

#include "../commons/commons.h"
#include "../traits/NonCopyable.h"

namespace hal::interfaces {

    class InterfaceDigitalGPIO : traits::NonCopyable<InterfaceDigitalGPIO> {
    public:

        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************

        /**
         * Default constructor.
         */
        InterfaceDigitalGPIO() :
                m_gpio_pin{0},
                m_gpio_dir{peripherals::gpio::Direction::OUT},
                m_gpio_pull{peripherals::gpio::Pull::NONE},
                m_gpio_func{peripherals::gpio::Function::NONE},
                m_gpio_irq{peripherals::gpio::IRQ::NONE},
                m_last_error{Error::NONE}
        {}

        /**
         * Instantiate a new GPIO pin and settings its direction
         *
         * @note Don't forget to initialise the object using init() method
         *
         * @param gpio_pin GPIO number
         * @param dir direction of the pin
         */
        InterfaceDigitalGPIO(const uint gpio_pin, const enum peripherals::gpio::Direction dir) :
                m_gpio_pin{gpio_pin},
                m_gpio_dir{dir},
                m_gpio_pull{peripherals::gpio::Pull::NONE},
                m_gpio_func{peripherals::gpio::Function::NONE},
                m_gpio_irq{peripherals::gpio::IRQ::NONE},
                m_last_error{Error::NONE}
        {}

        /**
         * Instantiate a new GPIO pin, set its direction and pulling mode
         *
         * @note Don't forget to initialise the object using @ref InterfaceGPIO::init() "init()" method
         *
         * @param gpio_pin GPIO number
         * @param dir direction of the pin
         * @param pull pulling mode of the pin
         */
        InterfaceDigitalGPIO(const uint gpio_pin, const enum peripherals::gpio::Direction dir, const enum peripherals::gpio::Pull pull) :
                m_gpio_pin{gpio_pin},
                m_gpio_dir{dir},
                m_gpio_pull{pull},
                m_gpio_func{peripherals::gpio::Function::NONE},
                m_gpio_irq{peripherals::gpio::IRQ::NONE},
                m_last_error{Error::NONE}
        {}

        /**
         * Instantiate a new GPIO pin, set its direction, pulling mode and function
         *
         * @note Don't forget to initialise the object using @ref InterfaceGPIO::init() "init()" method
         *
         * @param gpio_pin GPIO number
         * @param dir direction of the pin
         * @param pull pulling mode of the pin
         * @param func function of the pin
         */
        InterfaceDigitalGPIO(const uint gpio_pin, const enum peripherals::gpio::Direction dir, const enum peripherals::gpio::Pull pull, const enum peripherals::gpio::Function func) :
                m_gpio_pin{gpio_pin},
                m_gpio_dir{dir},
                m_gpio_pull{pull},
                m_gpio_func{func},
                m_gpio_irq{peripherals::gpio::IRQ::NONE},
                m_last_error{Error::NONE}
        {}

        /**
         * Instantiate a new GPIO pin by moving it from another one.
         *
         * @param other
         */
        InterfaceDigitalGPIO(InterfaceDigitalGPIO &&other) noexcept
        {
            if(this != &other) {

                m_gpio_pin = other.m_gpio_pin;
                m_gpio_dir = other.m_gpio_dir;
                m_gpio_pull = other.m_gpio_pull;
                m_gpio_func = other.m_gpio_func;
                m_gpio_irq = other.m_gpio_irq;
                m_last_error = other.m_last_error;

                // other.m_gpio_pin = 0;
                // other.m_gpio_dir = ???;
                // other.m_gpio_pull = Pull::NONE;
                other.m_gpio_func = peripherals::gpio::Function::NONE;
                // other.m_gpio_irq = IRQ::NONE;
                // other.m_last_error;
            }
        }

        /**
         * Destructor
         */
        ~InterfaceDigitalGPIO() override =default;

        // ****************************************************************
        //                            Operators
        // ****************************************************************

        /**
         * Move assignment operator
         *
         * @param other
         * @return
         */
        InterfaceDigitalGPIO &operator=(InterfaceDigitalGPIO &&other) noexcept {

            if(this != &other) {

                m_gpio_pin = other.m_gpio_pin;
                m_gpio_dir = other.m_gpio_dir;
                m_gpio_pull = other.m_gpio_pull;
                m_gpio_func = other.m_gpio_func;
                m_gpio_irq = other.m_gpio_irq;

                // other.m_gpio_pin = 0;
                // other.m_gpio_dir = ???;
                // other.m_gpio_pull = Pull::NONE;
                other.m_gpio_func = peripherals::gpio::Function::NONE;
                // other.m_gpio_irq = IRQ::NONE;
                // other.m_last_error = Error::None;
            }

            return *this;
        }

        /**
         *
         *  Operator that read into its GPIO pin then store the value into value
         *
         * @param value value to read
         * @return instance of the GPIO pin used to read
         */
        virtual InterfaceDigitalGPIO &operator>>(uint8_t &value) {

            value = read();

            return *this;
        }

        /**
         *
         * @param value value to write
         * @return instance of the GPIO pin to write
         */
        virtual InterfaceDigitalGPIO &operator<<(const uint8_t value) {

            write(value);

            return *this;
        }

        // ****************************************************************
        //                              Functions
        // ****************************************************************

        /**
         * Initialise the GPIO instance.
         *
         * @note This function is called in the implementation constructor.
         */
        virtual void init()=0;

        /**
         * De initialise the GPIO instance.
         *
         * @note This function is called in the implementation destructor.
         */
        virtual void deinit()=0;

        /**
         *
         * @return whether this instance has been inited
         */
        virtual bool inited() const {

            return m_gpio_func != peripherals::gpio::Function::NONE;
        }

        /**
         * Read into the GPIO.
         *
         * @return value read
         */
        virtual uint8_t read()=0;

        /**
         * Write into the GPIO.
         *
         * @param value value to write
         */
        virtual void write(const uint8_t value)=0;

        /**
         * Toggle the value of the GPIO
         */
        virtual void toggle() {

            write(!read());
        }

        // /**
        //  *
        //  * @param pin
        //  */
        // virtual bool setPin(const uint pin)=0;

        /**
         *
         */
        virtual uint getPin() const noexcept {

            return m_gpio_pin;
        }

        /**
         *
         * @param gpio_dir direction
         */
        virtual bool setDirection(const enum peripherals::gpio::Direction gpio_dir)=0;

        /**
         *
         * @return
         */
        virtual enum peripherals::gpio::Direction getDirection() const {

            return m_gpio_dir;
        }

        /**
         *
         * @param gpio_pull pulling mode
         */
        virtual bool setPull(const enum peripherals::gpio::Pull gpio_pull)=0;

        /**
         *
         * @return
         */
        virtual enum peripherals::gpio::Pull getPull() const {

            return m_gpio_pull;
        }

        /**
         *
         * @param gpio_func function of this gpio instance
         */
        virtual bool setFunction(const enum peripherals::gpio::Function gpio_func)=0;

        /**
         *
         */
        virtual enum peripherals::gpio::Function getFunction() const {

            return m_gpio_func;
        }

        // /**
        //  *
        //  * @param gpio_irq condition on which to raise an interrupt
        //  */
        // virtual bool setIRQ(const enum peripherals::gpio::IRQ gpio_irq)=0;

        // /**
        //  *
        //  * @return
        //  */
        // virtual enum peripherals::gpio::IRQ getIRQ() const {

        //     return m_gpio_irq;
        // }

        virtual enum Error getLastError() {

            return m_last_error;
        }

    protected:

        // ****************************************************************
        //                            Members
        // ****************************************************************

        uint m_gpio_pin; ///< Hold the gpio pin

        enum peripherals::gpio::Direction m_gpio_dir; ///< Hold the gpio direction, (Input; Output)
        enum peripherals::gpio::Pull m_gpio_pull; ///< Hold the gpio pulling mode ( Up; Down; ... )
        enum peripherals::gpio::Function m_gpio_func; ///< Hold the gpio function, (PWM; I2C; ...)
        enum peripherals::gpio::IRQ m_gpio_irq; ///< Hold the on which condition an interrupt should be raised (Rising or Falling Edge ... )

        enum Error m_last_error;

    private:
    };

} // hal::interface

#endif //EMBEDDEDLIBRARY_INTERFACEDIGITALGPIO_H
