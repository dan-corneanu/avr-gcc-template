#ifndef __DRIVERS_DIGITAL_IO_HEADER_INCLUDED__
#define __DRIVERS_DIGITAL_IO_HEADER_INCLUDED__

/**
 * Features to be implemented in this driver:
 *  - initial state
 *  - pin direction
 *  - alternate function for the pin. E.g. GPIO, SPI, PWM etc.
 *  - write pin
 *  - read pin
 */

#include "hardware/gpio.h"
#include <stdint.h>

void digital_io_toggle(const Gpio_PinT pin);

void digital_io_write(const Gpio_PinT pin, const Gpio_PinStateT state);

Gpio_PinStateT digital_io_read(const Gpio_PinT pin);

#endif
