import serial
import time
from random import randint
arduinoSerialPort = '/dev/ttyACM0'

# arduino serial
# serialData = 'road1/{}/road2/14'.format(objectsDeviation)


def serialEvent(serialData):
	serialData += "\n"
	serialData_encode = serialData.encode()
	print(serialData)
	ser = serial.Serial(arduinoSerialPort)
	ser.baudrate = 9600
	ser.write(serialData_encode)
	print(serialData_encode)
	time.sleep(1)
	ser.close()
#####


for i in range(10):
	# data = "road1/{}/road2/{}".format(randint(4,15), randint(4,15))

	data = "hello/{}".format(randint(0,1))
	serialEvent(data)
