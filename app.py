import numpy as np
import cv2
from time import sleep
import serial

arduinoSerialPort = '/dev/ttyACM0'

sdThresh = 7
font = cv2.FONT_HERSHEY_SIMPLEX

def distMap(frame1, frame2):
	frame1_32 = np.float32(frame1)
	frame2_32 = np.float32(frame2)
	diff32 = frame1_32 - frame2_32
	norm32 = np.sqrt(diff32[:,:,0]**2 + diff32[:,:,1]**2 + diff32[:,:,2]**2)/np.sqrt(255**2 + 255**2 + 255**2)
	dist = np.uint8(norm32*255)
	return dist

# camera_stream = "http://127.0.0.1:5000/video_feed"
# camera_stream = "http://192.168.137.160:81/stream"
# camera_stream = 0
camera_stream = input("type cam id you want to stream, or url for a webcam: ")

cap = cv2.VideoCapture(int(camera_stream))
 
_, frame1 = cap.read()
_, frame2 = cap.read()

app = False

while(1):

	if app == 0:
		_, frame3 = cap.read()
		cv2.imshow('dist', frame3)

		print("callibration.. press c to continue")
		k = cv2.waitKey(10) & 0xFF
		if k == ord('c'):
			app = 1

	if app == 1:
		# _, frame3 = cap.read()
		rows, cols, _ = np.shape(frame3)
		cv2.imshow('dist', frame3)
		dist = distMap(frame1, frame3)

		frame1 = frame2
		_, frame2 = cap.read()
		# apply Gaussian smoothing
		mod = cv2.GaussianBlur(dist, (9,9), 0)
		# apply thresholding
		_, thresh = cv2.threshold(mod, 100, 255, 0)
		# calculate st dev test
		_, stDev = cv2.meanStdDev(mod)
		cv2.imshow('dist', mod)
		cv2.putText(frame2, "Sensor - {}".format(round(stDev[0][0],0)), (70, 70), font, 1, (255, 0, 255), 1, cv2.LINE_AA)
		if stDev > sdThresh:
			# _, frameCallib = cap.read()
			objectsDeviation = round(stDev[0][0],0)
		
			serialData = 'road1/{}/road2/14'.format(objectsDeviation)
			serialData_encode=serialData.encode()
			print(serialData)
			ser = serial.Serial(arduinoSerialPort)
			ser.baudrate = 9600
			ser.write(serialData_encode)
			print(serialData_encode)
			time.sleep(1)
			ser.close()
			# print(objectsDeviation)

		# if stDev <= 5.5:
		# 	_, frame3 = cap.read()
 
	cv2.imshow('frame', frame2)
	if cv2.waitKey(1) & 0xFF == 27:
		break

	if cv2.waitKey(33) == ord('a'):
		print('callib called')
		callibrate()
cap.release()
cv2.destroyAllWindows()