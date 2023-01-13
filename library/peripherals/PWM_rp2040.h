//
// Created by marmelade on 16/11/22.
//

#ifndef EMBEDDEDLIBRARY_PWM_RP2040_H
#define EMBEDDEDLIBRARY_PWM_RP2040_H

#include <hardware/clocks.h>
#include <hardware/regs/clocks.h>
#include "hardware/pwm.h"

#include "../commons/commons.h"

static uint duty_cycle_to_pulse_width(const uint duty_cycle, const uint frequency) {

    return duty_cycle * (1/frequency) / 100;
}

namespace eml::hal::peripherals {

    class PWM : public interfaces::InterfacePWM {
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


        // ****************************************************************
        //                          Static Functions
        // ****************************************************************

        static PWM &getInstance(const pin_t &pin) {

            switch(PIN{pin.pin}) {
                // PWM_A[0]
                default:
                case PIN::PIN0:
                case PIN::PIN16:
                    static PWM s_pwm_instance_a0{pin};
                    return s_pwm_instance_a0;

                // PWM_A[1]
                case PIN::PIN2:
                case PIN::PIN18:
                    static PWM s_pwm_instance_a1{pin};
                    return s_pwm_instance_a1;

                // PWM_A[2]
                case PIN::PIN4:
                case PIN::PIN20:
                    static PWM s_pwm_instance_a2{pin};
                    return s_pwm_instance_a2;

                // PWM_A[3]
                case PIN::PIN6:
                case PIN::PIN22:
                    static PWM s_pwm_instance_a3{pin};
                    return s_pwm_instance_a3;

                // PWM_A[4]
                case PIN::PIN8:
                    static PWM s_pwm_instance_a4{pin};
                    return s_pwm_instance_a4;

                // PWM_A[5]
                case PIN::PIN10:
                case PIN::PIN26:
                    static PWM s_pwm_instance_a5{pin};
                    return s_pwm_instance_a5;

                // PWM_A[6]
                case PIN::PIN12:
                case PIN::PIN28:
                    static PWM s_pwm_instance_a6{pin};
                    return s_pwm_instance_a6;

                // PWM_A[7]
                case PIN::PIN14:
                    static PWM s_pwm_instance_a7{pin};
                    return s_pwm_instance_a7;

                // PWM_B[0]
                case PIN::PIN1:
                case PIN::PIN17:
                    static PWM s_pwm_instance_b0{pin};
                    return s_pwm_instance_b0;

                // PWM_B[1]
                case PIN::PIN3:
                case PIN::PIN19:
                    static PWM s_pwm_instance_b1{pin};
                    return s_pwm_instance_b1;

                // PWM_B[2]
                case PIN::PIN5:
                case PIN::PIN21:
                    static PWM s_pwm_instance_b2{pin};
                    return s_pwm_instance_b2;

                // PWM_B[3]
                case PIN::PIN7:
                    static PWM s_pwm_instance_b3{pin};
                    return s_pwm_instance_b3;

                // PWM_B[4]
                case PIN::PIN9:
                    static PWM s_pwm_instance_b4{pin};
                    return s_pwm_instance_b4;

                // PWM_B[5]
                case PIN::PIN11:
                case PIN::PIN27:
                    static PWM s_pwm_instance_b5{pin};
                    return s_pwm_instance_b5;

                // PWM_B[6]
                case PIN::PIN13:
                    static PWM s_pwm_instance_b6{pin};
                    return s_pwm_instance_b6;

                // PWM_B[7]
                case PIN::PIN15:
                    static PWM s_pwm_instance_b7{pin};
                    return s_pwm_instance_b7;

            }
        }

        // ****************************************************************
        //                             Functions
        // ****************************************************************

        bool init(const uint32_t frequency, const uint8_t duty_cycle, bool start) override {

            uint32_t clock_{frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS)};

            uint32_t wrap_ = clock_ / frequency;

            pwm_config_set_wrap(&m_config, wrap_);
            pwm_init(pwm_gpio_to_slice_num(m_pwm_pin.pin), &m_config, start);
            pwm_set_gpio_level(m_pwm_pin.pin, duty_cycle * wrap_ / 100);

            if(start) {
                enable();
            }

            m_duty_cycle = duty_cycle;
            m_frequency = frequency;

            return false;
        }

        void enable() override {

            pwm_set_enabled(pwm_gpio_to_slice_num(m_pwm_pin.pin), true);
        }

        void disable() override {

            pwm_set_enabled(pwm_gpio_to_slice_num(m_pwm_pin.pin), false);
        }

        void setFrequency(const uint32_t frequency, bool start) override {

            disable();

            uint32_t clock_ = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);

            uint32_t wrap_ = clock_ / frequency;
            pwm_config_set_wrap(&m_config, wrap_);

            pwm_init(pwm_gpio_to_slice_num(m_pwm_pin.pin), &m_config, start);
            pwm_set_gpio_level(m_pwm_pin.pin, m_duty_cycle * wrap_ / 100);

            m_frequency = frequency;
        }

        void setDutyCycle(uint8_t duty_cycle) override {

            m_duty_cycle = duty_cycle;

            uint32_t clock_ = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);

            uint32_t wrap_ = clock_ / m_frequency;

            pwm_set_gpio_level(m_pwm_pin.pin, duty_cycle * wrap_ / 100);
        }

        [[nodiscard]] uint8_t getPulseWidth() const override {

            return duty_cycle_to_pulse_width(m_duty_cycle, m_frequency);
        }

        uint read() override {

            return pwm_get_counter(pwm_gpio_to_slice_num(m_pwm_pin.pin));
        }

        void write(const uint value) override {

            pwm_set_gpio_level(m_pwm_pin.pin, value);
        }

    protected:
        explicit PWM(const pin_t &pwm_pin) : InterfacePWM() {m_pwm_pin = pwm_pin;}

        pwm_config m_config{};

    private:
    };
} // namespace eml::hal::peripherals

#endif //EMBEDDEDLIBRARY_PWM_RP2040_H
