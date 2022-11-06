//
// Created by marmelade on 06/11/22.
//

#ifndef EMBEDDEDLIBRARY_SPI_H
#define EMBEDDEDLIBRARY_SPI_H

#include "../interfaces/InterfaceSPI.h"

#ifdef LIB_PICO_PLATFORM
#include "SPI_rp2040.h"
// #elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__) // NOTE: NOT IMPLEMENTED YET
// #include "SPI_atmega328p.h"
#else
#error "No implementation available for your platform"
#endif

#endif //EMBEDDEDLIBRARY_SPI_H
