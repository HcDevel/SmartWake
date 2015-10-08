// Created 7. October 2015
// Robin Meis (blog.smartnoob.de)
// ATmega8
// See README.md for further details
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h" //Thanks to Peter Fleury for his UART library


void ADC_Init(void) {
  ADMUX = (1<<REFS1) | (1<<REFS0);
  ADCSRA = (1<<ADPS1) | (1<<ADPS0);
  ADCSRA |= (1<<ADEN);
  ADCSRA |= (1<<ADSC);
  while (ADCSRA & (1<<ADSC) );
  (void) ADCW;
}

uint16_t ADC_Read(uint8_t channel) {
  ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
  ADCSRA |= (1<<ADSC);
  while (ADCSRA & (1<<ADSC) );
  return ADCW;
}

uint16_t ADC_Read_Avg( uint8_t channel, uint8_t nsamples ) {
  uint32_t sum = 0;
  uint8_t i;
  for (i = 0; i < nsamples; ++i )
    sum += ADC_Read( channel );
  return (uint16_t)( sum / nsamples );
}

void battery_init(void) {
  //TODO: Port Pin for Transistor as output
  DDRB |= (1<<0); //Battery LOW (red) LED
}

void battery_check(void) {
  //TODO: Port Pin for Transistor high
  if (ADC_Read_Avg(0,2)<=820) {
    uart_puts("Low battery voltage! Replace soon!\n");
    PORTB ^= (1<<0);
  } else {
    uart_puts("Battery Voltage OK!\n");
    PORTB &=~ (1<<0);
  }
  //TODO: Port Pin for Transistor low
}


int main(void) {
  uart_init(UART_BAUD_SELECT(9600,F_CPU));
  ADC_Init();
  sei();
  battery_init();
  uint16_t dms;
  char buffer[10];
  for(;;) {
    dms = ADC_Read_Avg(1,2);
    itoa(dms, buffer,10);
    uart_puts(buffer);
    uart_puts("\n");
    battery_check();
    _delay_ms(1000);
  }
  return 0;
}
