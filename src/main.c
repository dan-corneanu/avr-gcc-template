#include <stdio.h>
#include <avr/interrupt.h>

#include "main.h"
#include "drivers/uart/uart.h"

#ifndef UART_BAUD_RATE
#define UART_BAUD_RATE 9600
#endif

inline static void init(void) {
  cli();

  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
  uart_attach_stdout();
    
  sei();
}

int main(void) {
  init();
  printf("Initialization done ...\n\r");
  
  for(;;) {
    __asm("NOP");
  }
}
