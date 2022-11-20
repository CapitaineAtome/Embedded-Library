//
// Created by marmelade on 16/11/22.
//

#ifndef EMBEDDEDLIBRARY_PWM_H
#define EMBEDDEDLIBRARY_PWM_H

#include "../interfaces/InterfacePWM.h"

#ifdef LIB_PICO_PLATFORM
#include "PWM_rp2040.h"
// #elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__) // NOTE: NOT IMPLEMENTED YET
// #include "PWM_atmega328p.h"
#else
#error "No implementation available for your platform"
#endif

#endif //EMBEDDEDLIBRARY_PWM_H
