#include "cfg.h"
#include "hardware/gpio.h"
#include <stdint.h>

// Configure all the pins for a particular board here.
const Gpio_PinConfigT DIGITAL_IO_CONFIG[] =
  {
    // Led connected to D13 on my board. This should eventually
    // translate to PB5.
    { .pin = ON_BOARD_RED_LED, .function = GPIO, .direction = OUTPUT, .pull_up = false, .state = LOW },
    { .pin = EXTERNAL_SW_1,    .function = GPIO, .direction = INPUT,  .pull_up = true }
  };

const uint8_t DIGITAL_IO_CONFIG_SIZE = sizeof(DIGITAL_IO_CONFIG) / sizeof(Gpio_PinConfigT);
