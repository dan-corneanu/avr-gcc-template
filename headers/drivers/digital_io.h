#ifndef __DIGITAL_IO_HEADER_INCLUDED__
#define __DIGITAL_IO_HEADER_INCLUDED__

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

void digital_io_init(const Gpio_PinConfigType * config, uint8_t size);

void digital_io_toggle(const Gpio_PinType pin);

void digital_io_write(const Gpio_PinType pin, const Gpio_PinStateType state);

#endif
