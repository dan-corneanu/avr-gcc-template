#include <avr/sfr_defs.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "hardware/gpio.h"
#include "main.h"
#include "uart.h"
#include "cfg.h"
#include "drivers/gpio.h"
#include "drivers/digital_io.h"

#ifndef UART_BAUD_RATE
#define UART_BAUD_RATE 9600
#endif

inline static void init(void) {
  cli();

  gpio_init(DIGITAL_IO_CONFIG, DIGITAL_IO_CONFIG_SIZE);
  
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
  uart_attach_stdout();
    
  sei();
}

void delay(volatile uint32_t d) 
{
  while (d-- != 0)
    ;
}

void extInt0Callback(void);
  
int main(void) {
  init();
  printf("Initialization done ...\n\r");
  printf("Number of GPIO pins configured %d ...\n\r", DIGITAL_IO_CONFIG_SIZE);
  
  printf("DDRB  register %02x\n\r", DDRB);
  printf("PORTB register %02x\n\r", PORTB);
  printf("PINB  register %02x\n\r", PINB);

  gpio_registerExternalInterrupt(Ext_Int0, ExtInt_Change, extInt0Callback);
  
  /* while(1) {  */
  /*   digital_io_write(ON_BOARD_RED_LED, HIGH); */
  /*   delay(8000); */
  /*   digital_io_write(ON_BOARD_RED_LED, LOW); */
  /*   delay(800000); */
  /* } */

  /* while (1) { */
  /*   if(digital_io_read(EXTERNAL_SW_1) == LOW) { */
  /*     digital_io_write(ON_BOARD_RED_LED, HIGH); */
  /*   } else { */
  /*     digital_io_write(ON_BOARD_RED_LED, LOW); */
  /*   } */
  /* } */

  for(;;) {
    __asm("NOP");
  }
}

void extInt0Callback(void)
{
  if(digital_io_read(EXTERNAL_SW_1) == HIGH) {
    // LED off
    digital_io_write(ON_BOARD_RED_LED, LOW);
  } else {
    // LED on
    digital_io_write(ON_BOARD_RED_LED, HIGH);
  }
}
