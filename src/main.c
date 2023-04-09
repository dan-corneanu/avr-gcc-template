#include <stdio.h>
#include <avr/interrupt.h>

#include "hardware/gpio.h"
#include "main.h"
#include "uart.h"
#include "digital_io_cfg.h"
#include "drivers/digital_io.h"

#ifndef UART_BAUD_RATE
#define UART_BAUD_RATE 9600
#endif

inline static void init(void) {
  cli();

  digital_io_init(DIGITAL_IO_CONFIG, 1);
  
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
  uart_attach_stdout();
    
  sei();
}

void delay(volatile uint32_t d) 
{
  while (d-- != 0)
    ;
}

int main(void) {
  init();
  printf("Initialization done ...\n\r");

  while(1) { 
    digital_io_write(ON_BOARD_RED_LED, HIGH);
    delay(8000);
    digital_io_write(ON_BOARD_RED_LED, LOW);
    delay(800000);
  }
  
  for(;;) {
    __asm("NOP");
  }
}
