//
// Created by marmelade on 16/11/22.
//

#ifndef EMBEDDEDLIBRARY_PWM_RP2040_H
#define EMBEDDEDLIBRARY_PWM_RP2040_H

#include "hardware/pwm.h"

namespace eml::hal::peripherals::pwm {

    class PWM : interfaces::InterfacePWM {
    public:
        //****************************************************************
        //                   Constructors and Destructor
        //****************************************************************

        ~PWM() override =default;

        PWM(const PWM &)=delete;
        PWM(PWM &&)=delete;

        // ****************************************************************
        //                            Operators
        // ****************************************************************
        PWM &operator=(const PWM &)=delete;
        PWM &operator=(PWM &&)=delete;

        PWM &operator=(const uint) override {

            return *this;
        }

        PWM &operator++() override {

            return *this;
        }

        PWM &operator--() override {

            return *this;
        }

        PWM &operator+=(const uint) override {

            return *this;
        }

        PWM &operator-=(const uint) override {

            return *this;
        }


        // ****************************************************************
        //                          Static Functions
        // ****************************************************************

        static PWM &getInstance(const pin_t &pin) {

            switch(pin.pin) {
                // PWM_A[0]
                default:
                case GPIO0:
                case GPIO16:
                    static PWM s_pwm_instance_a0{pin};
                    return s_pwm_instance_a0;

                // PWM_A[1]
                case GPIO2:
                case GPIO18:
                    static PWM s_pwm_instance_a1{pin};
                    return s_pwm_instance_a1;

                // PWM_A[2]
                case GPIO4:
                case GPIO20:
                    static PWM s_pwm_instance_a2{pin};
                    return s_pwm_instance_a2;

                // PWM_A[3]
                case GPIO6:
                case GPIO22:
                    static PWM s_pwm_instance_a3{pin};
                    return s_pwm_instance_a3;

                // PWM_A[4]
                case GPIO8:
                    static PWM s_pwm_instance_a4{pin};
                    return s_pwm_instance_a4;

                // PWM_A[5]
                case GPIO10:
                case GPIO26:
                    static PWM s_pwm_instance_a5{pin};
                    return s_pwm_instance_a5;

                // PWM_A[6]
                case GPIO12:
                case GPIO28:
                    static PWM s_pwm_instance_a6{pin};
                    return s_pwm_instance_a6;

                // PWM_A[7]
                case GPIO14:
                    static PWM s_pwm_instance_a7{pin};
                    return s_pwm_instance_a7;

                // PWM_B[0]
                case GPIO1:
                case GPIO17:
                    static PWM s_pwm_instance_b0{pin};
                    return s_pwm_instance_b0;

                // PWM_B[1]
                case GPIO3:
                case GPIO19:
                    static PWM s_pwm_instance_b1{pin};
                    return s_pwm_instance_b1;

                // PWM_B[2]
                case GPIO5:
                case GPIO21:
                    static PWM s_pwm_instance_b2{pin};
                    return s_pwm_instance_b2;

                // PWM_B[3]
                case GPIO7:
                    static PWM s_pwm_instance_b3{pin};
                    return s_pwm_instance_b3;

                // PWM_B[4]
                case GPIO9:
                    static PWM s_pwm_instance_b4{pin};
                    return s_pwm_instance_b4;

                // PWM_B[5]
                case GPIO11:
                case GPIO27:
                    static PWM s_pwm_instance_b5{pin};
                    return s_pwm_instance_b5;

                // PWM_B[6]
                case GPIO13:
                    static PWM s_pwm_instance_b6{pin};
                    return s_pwm_instance_b6;

                // PWM_B[7]
                case GPIO15:
                    static PWM s_pwm_instance_b7{pin};
                    return s_pwm_instance_b7;

            }
        }

        // ****************************************************************
        //                             Functions
        // ****************************************************************

        bool init(const uint32_t frequency, const uint8_t duty_cycle, bool start) override {

        }

        void setFrequency(const uint32_t frequency, bool start) {

        }

        void setDutyCycle(uint8_t duty_cycle) override {

        }

        uint8_t getPulseWidth() const override {

        }

        uint read() override {

        }

        void write(const uint value) override {

        }

    protected:
        explicit PWM(const pin_t &pwm_pin) : InterfacePWM() {}

    private:
    };
} // namespace eml::hal::peripherals::pwm

#endif //EMBEDDEDLIBRARY_PWM_RP2040_H
