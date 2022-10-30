//
// Created by marmelade on 30/10/22.
//

#ifndef EMBEDDEDLIBRARY_UART_H
#define EMBEDDEDLIBRARY_UART_H

#include "../interfaces/InterfaceUART.h"

#ifdef HAL_RP2040
#include "UART_rp2040.h"
// #elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__) // NOTE: NOT IMPLEMENTED YET
// #include "UART_atmega328p.h"
#else
#error "No implementation available for your platform"
#endif

#endif //EMBEDDEDLIBRARY_UART_H
