# file comments

## imageGetter
return the position of a given object among those defined in the yolo coco.names file.
are needed the file yolov3.weights and yolov3.cfg.


## directionHandler
using the imageGetter file, process the coordinates and manages the communication with the arduino 
in charge to control the motors. 

## arduinoMovement
receive the information from the directionHandler script, and rules the motors' input consequently.

## 
