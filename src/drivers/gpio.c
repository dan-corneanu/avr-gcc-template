#include "drivers/gpio.h"
#include "hardware/gpio.h"
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>

Gpio_InterruptCallback_t * EXT_INTERRUPT_CALLBACKS[NUM_Ext_Int] =
{
  NULL,
  NULL
};

void gpio_init(const Gpio_PinConfigT * config, uint8_t size)
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

void gpio_registerExternalInterrupt(
				    const Gpio_ExternalInterruptT interrupt,
				    const Gpio_ExternalInterruptTriggerT trigger,
				    Gpio_InterruptCallback_t * callback)
{
  EXT_INTERRUPT_CALLBACKS[interrupt] = callback;
  
  // Set up the EICRA – External Interrupt Control Register A.
  EICRA &= ~(3 << (interrupt << 1));
  EICRA |= (trigger << (interrupt << 1));

  // Clear the EIFR – External Interrupt Flag Register.
  EIFR |= (1 << interrupt);
  
  // Set up the EIMSK -  External Interrupt Mask Register.
  EIMSK |= (1 << interrupt);
}

ISR(INT0_vect)
{
  // The flag is cleared when the interrupt routine is executed.
  (*EXT_INTERRUPT_CALLBACKS[0])();
}

ISR(INT1_vect)
{
  // The flag is cleared when the interrupt routine is executed.
  (*EXT_INTERRUPT_CALLBACKS[1])();
}
