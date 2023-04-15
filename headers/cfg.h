#ifndef __CFG_HEADER_INCLUDED__
#define __CFG_HEADER_INCLUDED__

#include "hardware/gpio.h"
#include <stdint.h>

#define ON_BOARD_RED_LED PORTB_5
#define EXTERNAL_SW_1    PORTD_2

// Configure all the pins for a particular board here.
extern const Gpio_PinConfigT DIGITAL_IO_CONFIG[];
extern const uint8_t DIGITAL_IO_CONFIG_SIZE;

#endif
