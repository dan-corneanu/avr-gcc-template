#include "hardware/gpio.h"

const uint8_t NUM_PINS_PER_PORT = 8;

uint8_t volatile * const PORTS_DATA_REGISTER[NUM_GPIO_PORTS] =
  {
    (uint8_t*) &PORTB,
    (uint8_t*) &PORTC,
    (uint8_t*) &PORTD
  };

uint8_t volatile * const PORTS_DATA_DIRECTION_REGISTER[NUM_GPIO_PORTS] =
  {
    (uint8_t*) &DDRB,
    (uint8_t*) &DDRC,
    (uint8_t*) &DDRD
  };

uint8_t volatile * const PORTS_INPUT_PIN_REGISTER[NUM_GPIO_PORTS] =
  {
    (uint8_t*) &PINB,
    (uint8_t*) &PINC,
    (uint8_t*) &PIND
  };
