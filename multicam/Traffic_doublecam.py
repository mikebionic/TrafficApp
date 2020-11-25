import numpy as np
import cv2

sdThresh = 7
font = cv2.FONT_HERSHEY_SIMPLEX

import serial
import time
arduinoSerialPort = '/dev/ttyACM0'

def serialEvent(serialData):
	serialData += "\n"
	serialData_encode = serialData.encode()
	ser = serial.Serial(arduinoSerialPort)
	ser.baudrate = 9600
	ser.write(serialData_encode)
	time.sleep(0.1)
	ser.close()


def distMap(frame1, frame2):
	frame1_32 = np.float32(frame1)
	frame2_32 = np.float32(frame2)
	diff32 = frame1_32 - frame2_32
	norm32 = np.sqrt(diff32[:,:,0]**2 + diff32[:,:,1]**2 + diff32[:,:,2]**2)/np.sqrt(255**2 + 255**2 + 255**2)
	dist = np.uint8(norm32*255)
	return dist

video_capture_0 = cv2.VideoCapture(0)
video_capture_1 = cv2.VideoCapture(2)

_, frame1_0 = video_capture_0.read()
_, frame2_0 = video_capture_0.read()

_, frame1_1 = video_capture_1.read()
_, frame2_1 = video_capture_1.read()


app = False

while True:
	if app == False:
		_, frame3_0 = video_capture_0.read()
		_, frame3_1 = video_capture_1.read()

		cv2.imshow('Camera_0', frame3_0)
		cv2.imshow('Camera_1', frame3_1)

		print("callibration.. press c to continue")
		k = cv2.waitKey(10) & 0xFF
		if k == ord('c'):
			app = True

	# ret0, frame0 = video_capture_0.read()
	# ret1, frame1 = video_capture_1.read()

	if app == True:
		rows_0, cols_0, _ = np.shape(frame3_0)
		rows_1, cols_1, _ = np.shape(frame3_1)

		cv2.imshow('Camera_0', frame3_0)
		cv2.imshow('Camera_1', frame3_1)
		
		dist_0 = distMap(frame1_0, frame3_0)
		dist_1 = distMap(frame1_1, frame3_1)

		frame1_0 = frame2_0
		_, frame2_0 = video_capture_0.read()

		frame1_1 = frame2_1
		_, frame2_1 = video_capture_1.read()

		mod_0 = cv2.GaussianBlur(dist_0, (9,9), 0)
		_, thresh_0 = cv2.threshold(mod_0, 100, 255, 0)
		_, stDev_0 = cv2.meanStdDev(mod_0)


		mod_1 = cv2.GaussianBlur(dist_1, (9,9), 0)
		_, thresh_1 = cv2.threshold(mod_1, 100, 255, 0)
		_, stDev_1 = cv2.meanStdDev(mod_1)


		cv2.imshow('Camera_0', mod_0)
		cv2.imshow('Camera_1', mod_1)

		cv2.putText(frame2_0, "Sensor_0 - {}".format(round(stDev_0[0][0],0)), (70, 70), font, 1, (255, 0, 255), 1, cv2.LINE_AA)
		cv2.putText(frame2_1, "Sensor_1 - {}".format(round(stDev_1[0][0],0)), (70, 70), font, 1, (255, 0, 255), 1, cv2.LINE_AA)

		if (stDev_0 > sdThresh or stDev_1 > sdThresh):
			objectsDeviation_0 = round(stDev_0[0][0],0)
			objectsDeviation_1 = round(stDev_1[0][0],0)
			print("deviation: {}, {}".format(objectsDeviation_0, objectsDeviation_1))
			deviationData = "road1/{}/road2/{}".format(objectsDeviation_0,objectsDeviation_1)
			serialEvent(deviationData)


	if cv2.waitKey(1) & 0xFF == ord('q'):
		break

video_capture_0.release()
video_capture_1.release()
cv2.destroyAllWindows()