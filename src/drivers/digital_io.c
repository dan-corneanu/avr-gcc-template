#include "drivers/digital_io.h"
#include "hardware/gpio.h"
#include <stdint.h>

inline uint8_t c_pin_number(const Gpio_PinType pin) {
  return pin % NUM_PINS_PER_PORT;
}

inline uint8_t c_port_number(const Gpio_PinType pin) {
  return pin / NUM_PINS_PER_PORT;
}

void digital_io_init(const Gpio_PinConfigType * config, uint8_t size)
{
  uint8_t port_number = 0;
  uint8_t pin_number = 0;
  
  for(uint8_t i = 0; i < size; i++) {
    port_number = c_port_number(config[i].pin);
    pin_number = c_pin_number(config[i].pin);

    switch (config[i].function) {
    case GPIO :
      break;
    case ADC_INPUT :
      break;
    }
    
    if (config[i].direction == INPUT) {
      *PORTS_DATA_DIRECTION_REGISTER[port_number] &= ~(1 << pin_number);
      if(config[i].pull_up) {
	// Enable pull up resistor.
	*PORTS_DATA_REGISTER[port_number] |= (1 << pin_number);
      } else {
	*PORTS_DATA_REGISTER[port_number] &= ~(1 << pin_number);
      }
    } else {
      *PORTS_DATA_DIRECTION_REGISTER[port_number] |= (1 << pin_number);
      if(config[i].state == HIGH) {
	*PORTS_DATA_REGISTER[port_number] |= (1 << pin_number);
      } else if(config[i].state == LOW) {
	*PORTS_DATA_REGISTER[port_number] &= ~(1 << pin_number);
      }
    }
  }
}

void digital_io_toggle(const Gpio_PinType pin)
{
  uint8_t port_number = c_port_number(pin);
  uint8_t pin_number = c_pin_number(pin);

  *PORTS_DATA_REGISTER[port_number] ^= (1 << pin_number);
}

void digital_io_write(const Gpio_PinType pin, const Gpio_PinStateType state)
{
  uint8_t port_number = c_port_number(pin);
  uint8_t pin_number = c_pin_number(pin);

  if(state == HIGH) {
    *PORTS_DATA_REGISTER[port_number] |= (1 << pin_number);
  } else if(state == LOW) {
    *PORTS_DATA_REGISTER[port_number] &= ~(1 << pin_number);
  }
}

Gpio_PinStateType digital_io_read(const Gpio_PinType pin)
{
  uint8_t port_number = c_port_number(pin);
  uint8_t pin_number = c_pin_number(pin);

  if(*PORTS_INPUT_PIN_REGISTER[port_number] & (1 << pin_number)) {
    return HIGH;
  } else {
    return LOW;
  }
}
