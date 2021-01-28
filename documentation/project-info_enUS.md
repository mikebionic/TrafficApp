# Automation system for traffic control, vehicle and pedestrian detection.

## Basic goals

This project is intended to improve road traffic processes and ensure pedestrian safety.
The program should:
+ Detect vehicles and read traffic information
+ Make calculations and set favorable traffic light times
+ Keep pedestrians and vehicles safe

## How does it work?

Using the technology of computer image and video processing, the program reads traffic conditions from cameras. This is necessary in order to obtain information about traffic congestion, the number of pedestrians.
The data is transferred to the microcontroller, which in turn controls the state and time of the traffic light.

## Activate the system

To start the system, you must use a computer or microcomputer with preinstalled software. Also connected to one of the USB connectors of the Arduino microprocessor. To get information about traffic, the program needs to indicate from which sources
you need to read the video stream. It can be two webcams connected to USB ports, or a link to online cameras.
After that, two windows with a video stream will appear on the graphical user interface of the computer. It is necessary for calibrating cameras. After calibrating, you must press the "C" key on the keyboard, after which the program will display two video streams with information about the proportions of objects on the road and their absence. If at this stage you start to arrange cars, the number of proportions will begin to increase and the data on occupancy will be sent to the microcontroller that controls the time of the traffic light. As a result, if there is more vehicle on one road than on the other, the microprocessor will set the time of the green light of the traffic light, determined from the proportion value.
Also, the software part of the image recognition system has another version, which provides machine learning and the creation of car models, according to which the recognition system and proportion calculation will work.

## Further development

The next steps would be:
+ improved recognition
+ determination of the required recognition zone for a clearer analysis
+ timely automatic calibrations
+ identifying traffic information on a web page for road safety officials

## Programming languages

Python version above 3.6
C++ with Arduino library

## Needed materials

Material | quantity
---------|------
RaspberryPi 4 | x1
Web camera / Network camera stream | x2
Arduino | x1
Led strip | x12 diodes