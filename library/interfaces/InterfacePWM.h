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

        virtual bool init(const uint pwm_pin, const uint frequency, const uint8_t duty_cycle, bool start)=0;

        virtual uint read()=0;
        virtual void write(const uint value)=0;
        // InterfaceUART &getInstance(const uint8_t instance) override =0;

    protected:
        // ****************************************************************
        //                    Constructors and Destructor
        // ****************************************************************

        InterfacePWM()= default;

        uint m_pwm_pin;
        /// In kHz
        uint32_t m_frequency;
        /// Between [0; 100]
        uint8_t m_duty_cycle;

    private:
    };

} // namespace hal::interfaces
#endif //EMBEDDEDLIBRARY_INTERFACEPWM_H
