import time
import serial
import datetime

ser = serial.Serial(port='/dev/ttyUSB0', baudrate=9600) #Connection parameters

ser.isOpen()
startzeit = time.time()
print('Time,Seconds,Resistance') #Output as CSV

while 1:
        out = ''
        time.sleep(1)
        while ser.inWaiting() > 0:
            out += str(ser.read(1))[2:-1]

        if out != '':
            print (datetime.datetime.fromtimestamp(time.time()).strftime('%H:%M:%S') + ',' + str(time.time() - startzeit).split('.')[0] + ',' + out.split("\\n")[0]) #Output as CSV
