import cv2 
from imutils.video import VideoStream
import numpy as np
import datetime
import imutils
import time
import cv2

cascade_data = cv2.CascadeClassifier('../cascade_datas/cars_cascade2.xml')
cars_image = None
total = 0
# cars_image = ('./images/cars.jpg')

# webcam = cv2.VideoCapture(0)
# picam = cv2.VideoCapture(0)

picam = VideoStream(src=0).start()
webcam = VideoStream(src=2).start()
time.sleep(2.0)
cameras = [picam,webcam]
scaling_factor = 0.5

while True:
	frames = []
	for (stream,name) in zip(cameras,("picam","webcam")):
		frame = stream.read()
		if total < 32:
			frames.append(frame)
			continue

		frames.append(frame)

		data_rects = cascade_data.detectMultiScale(frame, scaleFactor=1.3, minNeighbors=3)
		print(name+' '+str(len(data_rects)))
		for (x,y,w,h) in data_rects:        
			cv2.rectangle(frame, (x,y), (x+w,y+h), (0,255,0), 3)
	
	total += 1
	# for (frame, name) in zip(frames, ("picam","webcam")): 
	# 	cv2.imshow(name, frame)
	
	c = cv2.waitKey(1)    
	if c == 27:        
		break

cv2.destroyAllWindows()
webcam.stop()
picam.stop()