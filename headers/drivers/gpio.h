#ifndef __DRIVERS_GPIO_HEADER_INCLUDED__
#define __DRIVERS_GPIO_HEADER_INCLUDED__

#include "hardware/gpio.h"

typedef void Gpio_InterruptCallback_t (void);
typedef enum
  {
    Ext_Int0,
    Ext_Int1,
    NUM_Ext_Int
  } Gpio_ExternalInterruptT;
typedef enum
  {
    ExtInt_Low,
    ExtInt_Change,
    ExtInt_Falling,
    ExtInt_Rising
  } Gpio_ExternalInterruptTriggerT;

void gpio_init(const Gpio_PinConfigT * config, uint8_t size);

void gpio_registerExternalInterrupt(
				    const Gpio_ExternalInterruptT,
				    const Gpio_ExternalInterruptTriggerT,
				    Gpio_InterruptCallback_t *);

#endif
