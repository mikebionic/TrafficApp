import cv2 
import numpy as np
cascade_data = cv2.CascadeClassifier('./cascade_datas/cars_cascade1.xml')
cars_image = ('./images/cars.jpg')

if cars_image:
    img = cv2.imread(cars_image)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    while True:
        frame = cascade_data.detectMultiScale(gray, 1.3, 5)
        cv2.imshow('Cars Detector', frame)
        # print (len(frame))
        c = cv2.waitKey(1)
        if c == 27:        
            break
    cap.release() 
    cv2.destroyAllWindows()

else:
    cap = cv2.VideoCapture(0)
    scaling_factor = 0.5

    while True:
        ret, frame = cap.read()
        data_rects = cascade_data.detectMultiScale(frame, scaleFactor=1.3, minNeighbors=3)
        for (x,y,w,h) in data_rects:        
            cv2.rectangle(frame, (x,y), (x+w,y+h), (0,255,0), 3)
        cv2.imshow('Cars Detector', frame)
        
        c = cv2.waitKey(1)    
        if c == 27:        
            break
    cap.release() 
    cv2.destroyAllWindows()