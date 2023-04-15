#include "drivers/digital_io.h"
#include "hardware/gpio.h"
#include <stdint.h>

void digital_io_toggle(const Gpio_PinT pin)
{
  uint8_t port_number = c_port_number(pin);
  uint8_t pin_number = c_pin_number(pin);

  *PORTS_DATA_REGISTER[port_number] ^= (1 << pin_number);
}

void digital_io_write(const Gpio_PinT pin, const Gpio_PinStateT state)
{
  uint8_t port_number = c_port_number(pin);
  uint8_t pin_number = c_pin_number(pin);

  if(state == HIGH) {
    *PORTS_DATA_REGISTER[port_number] |= (1 << pin_number);
  } else if(state == LOW) {
    *PORTS_DATA_REGISTER[port_number] &= ~(1 << pin_number);
  }
}

Gpio_PinStateT digital_io_read(const Gpio_PinT pin)
{
  uint8_t port_number = c_port_number(pin);
  uint8_t pin_number = c_pin_number(pin);

  if(*PORTS_INPUT_PIN_REGISTER[port_number] & (1 << pin_number)) {
    return HIGH;
  } else {
    return LOW;
  }
}
