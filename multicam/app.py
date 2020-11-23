from __future__ import print_function
from detector import BasicMotionDetector
from imutils.video import VideoStream
import numpy as np
import datetime
import imutils
import time
import cv2

print("[INFO] starting cameras...")
webcam = VideoStream(src=0).start()
picam = VideoStream(src=1).start()
time.sleep(2.0)

camMotion = BasicMotionDetector()
piMotion = BasicMotionDetector()
total = 0

while True:
	frames = []

	for (stream, motion) in zip((webcam, picam), (camMotion, piMotion)):
		frame = stream.read()
		frame = imutils.resize(frame, width=400)

		gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
		gray = cv2.GaussianBlur(gray, (21, 21), 0)
		locs = motion.update(gray)

		if total < 32:
			frames.append(frame)
			continue

		# # otherwise, check to see if motion was detected
		# if len(locs) > 0:
		# 	# initialize the minimum and maximum (x, y)-coordinates,
		# 	# respectively
		# 	(minX, minY) = (np.inf, np.inf)
		# 	(maxX, maxY) = (-np.inf, -np.inf)

		# 	# loop over the locations of motion and accumulate the
		# 	# minimum and maximum locations of the bounding boxes
		# 	for l in locs:
		# 		(x, y, w, h) = cv2.boundingRect(l)
		# 		(minX, maxX) = (min(minX, x), max(maxX, x + w))
		# 		(minY, maxY) = (min(minY, y), max(maxY, y + h))

		# 	# draw the bounding box
		# 	cv2.rectangle(frame, (minX, minY), (maxX, maxY),
		# 		(0, 0, 255), 3)
		
		# # update the frames list
		frames.append(frame)

	# increment the total number of frames read and grab the 
	# current timestamp
	total += 1
	timestamp = datetime.datetime.now()
	ts = timestamp.strftime("%A %d %B %Y %I:%M:%S%p")

	# loop over the frames a second time
	for (frame, name) in zip(frames, ("Webcam", "Picamera")):
		# draw the timestamp on the frame and display it
		cv2.putText(frame, ts, (10, frame.shape[0] - 10),
			cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)
		cv2.imshow(name, frame)

	# check to see if a key was pressed
	key = cv2.waitKey(1) & 0xFF

	# if the `q` key was pressed, break from the loop
	if key == ord("q"):
		break

# do a bit of cleanup
print("[INFO] cleaning up...")
cv2.destroyAllWindows()
webcam.stop()
picam.stop()