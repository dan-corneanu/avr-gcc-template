#ifndef __GPIO_HEADER_INCLUDED__
#define __GPIO_HEADER_INCLUDED__

#include <stdint.h>
#include <avr/io.h>
#include <stdbool.h>

/**
 * Data Register - PORTx
 * Data Direction Register - DDRx
 * Port Input Pins - PINx
 *   - this register is readonly.
 *   - writing a logic 1 in bit in PINx Register, will result in a toggle in
 *     the corresponding bit in the Data Register.
 *
 * Each port has an optional internal pull up resistor.
 *
 * When the reset condition becomes active, all port pins are
 * tri-stated even if no clocks are running.
 */

/* This section defines abstractions for the device registers. */

extern const uint8_t NUM_PINS_PER_PORT;

typedef enum
  {
    GPIOB,
    GPIOC,
    GPIOD,
    NUM_GPIO_PORTS
  } Gpio_PortType;

/**
 * Defines a table of pointers to the Data Register for each GPIO port
 * of the microcontroller.
 */
extern uint8_t volatile * const PORTS_DATA_REGISTER[NUM_GPIO_PORTS];

/**
 * Defines a table of pointers to the Data Direction Register for each
 * GPIO port of the microcontroller.
 */
extern uint8_t volatile * const PORTS_DATA_DIRECTION_REGISTER[NUM_GPIO_PORTS];

/**
 * Defines a table of pointers to the Pin Register for each GPIO port
 * of the microcontroller.
 */
extern uint8_t volatile * const PORTS_INPUT_PIN_REGISTER[NUM_GPIO_PORTS];

/* This section defines abstractions for the configuration tables. */

typedef enum
  {
    PORTB_0,
    PORTB_1,
    PORTB_2,
    PORTB_3,
    PORTB_4,
    ON_BOARD_RED_LED, // PB5, D13 on arduino
    PORTB_6,
    PORTB_7,
    PORTC_0,
    PORTC_1,
    PORTC_2,
    PORTC_3,
    PORTC_4,
    PORTC_5,
    PORTC_6,
    PORTC_7,
    PORTD_0,
    PORTD_1,
    PORTD_2,
    PORTD_3,
    PORTD_4,
    PORTD_5,
    PORTD_6,
    PORTD_7,
    NUM_GPIO_PINS
  } Gpio_PinType;

typedef enum
  {
    INPUT,
    OUTPUT
  } Gpio_PinDirectionType;

typedef enum
  {
    HIGH,
    LOW
  } Gpio_PinStateType;

typedef enum
  {
    GPIO,
    ADC_INPUT
  } Gpio_PinFunctionType;

typedef struct
{
  Gpio_PinType pin;
  Gpio_PinFunctionType function;
  Gpio_PinDirectionType direction;
  bool pull_up;
  Gpio_PinStateType state;
} Gpio_PinConfigType;

#endif
