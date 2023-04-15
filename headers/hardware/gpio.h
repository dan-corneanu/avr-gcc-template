#ifndef __HARDWARE_GPIO_HEADER_INCLUDED__
#define __HARDWARE_GPIO_HEADER_INCLUDED__

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
  } Gpio_PortT;

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
    PORTB_5, //D13 on arduino
    // PORTB_6, // NC
    // PORTB_7, // NC
    PORTC_0 = 8,
    PORTC_1,
    PORTC_2,
    PORTC_3,
    PORTC_4,
    PORTC_5,
    // PORTC_6, // NC
    // PORTC_7, // NC
    PORTD_0 = 16,
    PORTD_1,
    PORTD_2, // INT0
    PORTD_3, // INT1
    PORTD_4,
    PORTD_5,
    PORTD_6,
    PORTD_7,
    NUM_GPIO_PINS
  } Gpio_PinT;

typedef enum
  {
    INPUT,
    OUTPUT
  } Gpio_PinDirectionT;

typedef enum
  {
    HIGH,
    LOW
  } Gpio_PinStateT;

typedef enum
  {
    GPIO,
    ADC_INPUT
  } Gpio_PinFunctionT;

typedef struct
{
  Gpio_PinT pin;
  Gpio_PinFunctionT function;
  Gpio_PinDirectionT direction;
  bool pull_up;
  Gpio_PinStateT state;
} Gpio_PinConfigT;

static inline uint8_t c_pin_number(const Gpio_PinT pin) {
  return pin % NUM_PINS_PER_PORT;
}

static inline uint8_t c_port_number(const Gpio_PinT pin) {
  return pin / NUM_PINS_PER_PORT;
}

#endif
