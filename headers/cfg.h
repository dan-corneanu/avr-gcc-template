#ifndef __DIGITAL_CFG_HEADER_INCLUDED__
#define __DIGITAL_CFG_HEADER_INCLUDED__

#include "hardware/gpio.h"
#include <stdint.h>

#define ON_BOARD_RED_LED PORTB_5
#define EXTERNAL_SW_1    PORTB_4

// Configure all the pins for a particular board here.
extern const Gpio_PinConfigType DIGITAL_IO_CONFIG[];
extern const uint8_t DIGITAL_IO_CONFIG_SIZE;

#endif
