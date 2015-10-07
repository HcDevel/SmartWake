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


int main(void) {
  uart_init(UART_BAUD_SELECT(9600,F_CPU));
  ADC_Init();
  sei();
  char buffer[10];
  for(;;) {
    itoa(ADC_Read_Avg(0,2), buffer,10);
    uart_puts(buffer);
    uart_puts("\n");
    _delay_ms(1000);
  }
  return 0;
}
