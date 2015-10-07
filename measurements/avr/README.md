This program uses Peter Fleury's AVR UART lib to send the ADC value of PC0 (ADC0 on ATmega8) each second over UART with a baudrate of 9600 baud (Read-Only).

Each value is seperated by newlines (\n). The program was written to put the data into a CSV which is logged on a computer (see ../logger).
