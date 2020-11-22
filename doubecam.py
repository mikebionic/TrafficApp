import numpy as np
import cv2
from time import sleep
 
sdThresh = 10
font = cv2.FONT_HERSHEY_SIMPLEX

def distMap(frame1, frame2):
	frame1_32 = np.float32(frame1)
	frame2_32 = np.float32(frame2)
	diff32 = frame1_32 - frame2_32
	norm32 = np.sqrt(diff32[:,:,0]**2 + diff32[:,:,1]**2 + diff32[:,:,2]**2)/np.sqrt(255**2 + 255**2 + 255**2)
	dist = np.uint8(norm32*255)
	return dist
 
cv2.namedWindow('frame')
cv2.namedWindow('dist')

cv2.namedWindow('frame_2')
cv2.namedWindow('dist_2')

# camera_stream = "http://127.0.0.1:5000/video_feed"
# camera_stream = "http://192.168.137.160:81/stream"
camera_stream = 0
camera_stream_2 = 2

cap = cv2.VideoCapture(camera_stream)
cap_2 = cv2.VideoCapture(camera_stream_2)
 
_, frame1 = cap.read()
_, frame2 = cap.read()

_, frame2_1 = cap_2.read()
_, frame2_2 = cap_2.read()

app = False

while(1):

	if app == 0:
		_, frame3 = cap.read()
		_, frame2_3 = cap_2.read()

		cv2.imshow('dist', frame3)
		cv2.imshow('dist_2', frame2_3)

		print("callibration.. press c to continue")
		k = cv2.waitKey(10) & 0xFF
		if k == ord('c'):
			app = 1

	if app == 1:
		# _, frame3 = cap.read()
		rows, cols, _ = np.shape(frame3)
		rows, cols, _ = np.shape(frame2_3)

		cv2.imshow('dist', frame3)
		cv2.imshow('dist_2', frame2_3)
		
		dist = distMap(frame1, frame3)
		dist_2 = distMap(frame2_1, frame2_3)

		frame1 = frame2
		_, frame2 = cap.read()

		frame2_1 = frame2_2
		_, frame2_2 = cap_2.read()


		# apply Gaussian smoothing
		mod = cv2.GaussianBlur(dist, (9,9), 0)
		# apply thresholding
		_, thresh = cv2.threshold(mod, 100, 255, 0)
		# calculate st dev test
		_, stDev = cv2.meanStdDev(mod)
		cv2.imshow('dist', mod)
		cv2.putText(frame2, "Sensor - {}".format(round(stDev[0][0],0)), (70, 70), font, 1, (255, 0, 255), 1, cv2.LINE_AA)


		# apply Gaussian smoothing
		mod_2 = cv2.GaussianBlur(dist_2, (9,9), 0)
		# apply thresholding
		_, thresh_2 = cv2.threshold(mod_2, 100, 255, 0)
		# calculate st dev test
		_, stDev_2 = cv2.meanStdDev(mod_2)
		cv2.imshow('dist_2', mod_2)
		cv2.putText(frame2_2, "Sensor - {}".format(round(stDev_2[0][0],0)), (70, 70), font, 1, (255, 0, 255), 1, cv2.LINE_AA)
		

		if stDev > sdThresh:
			# _, frameCallib = cap.read()
			objectsDeviation = round(stDev[0][0],0)
			# print(objectsDeviation)

		# if stDev <= 5.5:
		# 	_, frame3 = cap.read()
 
	cv2.imshow('frame', frame2)
	cv2.imshow('frame_2', frame2_2)
	if cv2.waitKey(1) & 0xFF == 27:
		break

	if cv2.waitKey(33) == ord('a'):
		print('callib called')
		app = 0

cap.release()
cv2.destroyAllWindows()