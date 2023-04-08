#include <stdio.h>
#include <avr/interrupt.h>

#include "hardware/gpio.h"
#include "main.h"
#include "drivers/uart/uart.h"
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
  while (d-- != 0)     // loops while non-0 and decrements
    ;
}

int main(void) {
  init();
  printf("Initialization done ...\n\r");

  while(1) // forever loop
    { 
      digital_io_toggle(ON_BOARD_RED_LED);
      delay(80000); // 8 MHz / 800
    }
  
  for(;;) {
    __asm("NOP");
  }
}
