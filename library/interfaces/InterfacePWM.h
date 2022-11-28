//
// Created by marmelade on 13/11/22.
//

#ifndef EMBEDDEDLIBRARY_INTERFACEPWM_H
#define EMBEDDEDLIBRARY_INTERFACEPWM_H

#include <cstdlib>

#include "../traits/Singleton.h"
#include "InterfaceDigitalGPIO.h"

namespace hal::interfaces {

    class InterfacePWM : public traits::Singleton {
    public:
        // ****************************************************************
        //                              Enums
        // ****************************************************************

        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************

        /**
         * The destructor must call @ref hal::interfaces::InterfacePWM::deinit() "deinit()" in the concrete class
         */
        ~InterfacePWM() override =default;

        InterfacePWM(const InterfacePWM &)=delete;
        InterfacePWM(InterfacePWM &&)=delete;

        // ****************************************************************
        //                            Operators
        // ****************************************************************

        InterfacePWM &operator=(const InterfacePWM &)=delete;
        InterfacePWM &operator=(InterfacePWM &&)=delete;

        virtual InterfacePWM &operator=(const uint)=0;
        virtual InterfacePWM &operator++()=0;
        virtual InterfacePWM &operator--()=0;
        virtual InterfacePWM &operator+=(const uint)=0;
        virtual InterfacePWM &operator-=(const uint)=0;

        // ****************************************************************
        //                             Functions
        // ****************************************************************

        virtual bool init(const uint32_t frequency, const uint8_t duty_cycle, bool start)=0;

        virtual void setFrequency(uint32_t frequency, bool start)=0;
        virtual uint32_t getFrequency() const {

            return m_frequency;
        }

        virtual void setDutyCycle(uint8_t duty_cycle)=0;

        virtual uint8_t getDutyCycle() const {

            return m_duty_cycle;
        }

        virtual uint8_t getPulseWidth() const =0;

        virtual uint read()=0;
        virtual void write(const uint value)=0;

        // InterfacePWM &getInstance(const uint8_t instance) override =0;

    protected:
        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************

        InterfacePWM() : m_pwm_pin{}, m_frequency{}, m_duty_cycle{} {}

        pin_t m_pwm_pin;
        /// In kHz
        uint32_t m_frequency;
        /// Between [0; 100]
        uint8_t m_duty_cycle;

    private:
    };

} // namespace hal::interfaces
#endif //EMBEDDEDLIBRARY_INTERFACEPWM_H
