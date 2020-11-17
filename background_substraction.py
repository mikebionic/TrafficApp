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
 
cap = cv2.VideoCapture(0)
 
_, frame1 = cap.read()
_, frame2 = cap.read()
_, frameCallib = cap.read()

while(True):
	_, frame3 = cap.read()
	rows, cols, _ = np.shape(frame3)
	cv2.imshow('dist', frame3)
	dist = distMap(frameCallib, frame3)
 
	frame1 = frame2
	frame2 = frame3
 
	# apply Gaussian smoothing
	mod = cv2.GaussianBlur(dist, (9,9), 0)
 
	# apply thresholding
	_, thresh = cv2.threshold(mod, 100, 255, 0)
 
	# calculate st dev test
	_, stDev = cv2.meanStdDev(mod)
 
	cv2.imshow('dist', mod)
	cv2.putText(frame2, "Standard Deviation - {}".format(round(stDev[0][0],0)), (70, 70), font, 1, (255, 0, 255), 1, cv2.LINE_AA)
	if stDev > sdThresh:
		# _, frameCallib = cap.read()
		objectsDeviation = round(stDev[0][0],0)
		print(objectsDeviation)
		# print("Motion detected.. Do something!!!");

 
	cv2.imshow('frame', frame2)
	if cv2.waitKey(1) & 0xFF == 27:
		break

	# if cv2.waitKey(33) == ord('a'):
	# 	print('callib called')
	# 	callibrate()
cap.release()
cv2.destroyAllWindows()