#ifndef __DIGITAL_IO_CFG_HEADER_INCLUDED__
#define __DIGITAL_IO_CFG_HEADER_INCLUDED__

#include "hardware/gpio.h"

// Configure all the pins for a particular board here.

const Gpio_PinConfigType DIGITAL_IO_CONFIG[] =
  {
    // LED connected to D13 on my board. This should eventually
    // translate to PB5.
    { .pin = ON_BOARD_RED_LED, .function = GPIO, .direction = OUTPUT, .pull_up = false, .state = LOW }
  };

#endif
