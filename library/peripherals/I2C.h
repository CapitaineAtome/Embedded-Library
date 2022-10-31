//
// Created by marmelade on 30/10/22.
//

#ifndef EMBEDDEDLIBRARY_I2C_H
#define EMBEDDEDLIBRARY_I2C_H

#include "../interfaces/InterfaceI2C.h"

#ifdef HAL_RP2040
#include "I2C_rp2040.h"
// #elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__) // NOTE: NOT IMPLEMENTED YET
// #include "DigitalOut_atmega328p.h"
#else
#error "No implementation available for your platform"
#endif

#endif //EMBEDDEDLIBRARY_I2C_H
