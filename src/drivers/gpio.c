#include "drivers/gpio.h"

void gpio_init(const Gpio_PinConfigType * config, uint8_t size)
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
