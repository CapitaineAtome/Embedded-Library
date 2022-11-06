//
// Created by marmelade on 30/10/22.
//

#ifndef EMBEDDEDLIBRARY_I2C_H
#define EMBEDDEDLIBRARY_I2C_H

#include "../interfaces/InterfaceI2C.h"

#ifdef LIB_PICO_PLATFORM
#include "I2C_rp2040.h"
// #elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__) // NOTE: NOT IMPLEMENTED YET
// #include "I2C_atmega328p.h"
#else
#error "No implementation available for your platform"
#endif

#endif //EMBEDDEDLIBRARY_I2C_H
