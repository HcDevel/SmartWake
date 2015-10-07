The files stored in this directory were used to log data before the real implementation started.

The AVR was programmed to send the ADC value each second over UART, the Python3 program receives the data and prints it CSV formated on terminal. By redirecting the output into a CSV file (python3 datalogger.py > visualization.csv), it can be imported by Open Office and can be copied & pasted into the file visualization.ods which creates a graph.

Have a nice night and measure the values...
