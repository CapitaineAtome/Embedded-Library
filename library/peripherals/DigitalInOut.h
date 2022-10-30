//
// Created by marmelade on 07/10/22.
//

#ifndef EMBEDDEDLIBRARY_DIGITALINOUT_H
#define EMBEDDEDLIBRARY_DIGITALINOUT_H

#include "../interfaces/InterfaceDigitalGPIO.h"

#ifdef HAL_RP2040
#include "DigitalInOut_rp2040.h"
// #elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__) // NOTE: NOT IMPLEMENTED YET
// #include "DigitalOut_atmega328p.h"
#else
#error "No implementation available for your platform"
#endif


#endif //EMBEDDEDLIBRARY_DIGITALINOUT_H
