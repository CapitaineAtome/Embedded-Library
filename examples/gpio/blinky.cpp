//
// Created by marmelade on 28/11/22.
//
#include "commons/commons.h"
#include "peripherals/DigitalInOut.h"

#ifdef LIB_PICO_PLATFORM
#define LED_PIN PICO_DEFAULT_LED_PIN // Default LED on the raspberry pi pico ( not the pico w )
#else
// To define for other platform
#define LED_PIN 1
#endif

int main() {

    // Instantiate the LED at the pin LED_PIN as an output.
    auto led{eml::hal::peripherals::gpio::DigitalInOut(eml::hal::pin(LED_PIN),
                                                  eml::hal::peripherals::gpio::Direction::OUT)};

    // Initialise the LED
    led.init();

    while(true) {

        // Toggle the light
        led.toggle();

        // Every few milliseconds
        eml::hal::sleep_millis(500);
    }

    return 0;
}
