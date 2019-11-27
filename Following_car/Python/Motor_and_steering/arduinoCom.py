import serial
import time

ser = serial.Serial('/dev/ttyACM1',9600)
ser.close()
ser.open()
time.sleep(5)

ser.write(str.encode('test'))
try:
    while True:
        response = ser.readline()
        print(response)
except KeyboardInterrupt:
    ser.close()