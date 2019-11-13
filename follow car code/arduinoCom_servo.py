import cv2
import os
import numpy as np
import picamera
import time
import picamera.array
import serial

os.nice(20)

ser = serial.Serial('/dev/ttyACM0',115200)
ser.close()
ser.open()
time.sleep(5)


#function for setting the servo angle
def SetAngle(angle):
    duty = angle / 18 + 2
    datasent = str.encode(chr(int(angle)))
    print("Data sent: ")
    print(datasent)
    ser.write(datasent)
    time.sleep(0.01)
    
    
def translate(value, leftMin, leftMax, rightMin, rightMax):
    # Figure out how 'wide' each range is
    leftSpan = leftMax - leftMin
    rightSpan = rightMax - rightMin

    # Convert the left range into a 0-1 range (float)
    valueScaled = float(value - leftMin) / float(leftSpan)

    # Convert the 0-1 range into a value in the right range.
    return round((rightMin + (valueScaled * rightSpan)),0)




class DetectBall(picamera.array.PiRGBAnalysis):
    
    def analyse(self, a):

        g = np.copy(a)
        
    #set blue and red channels to 0
        g[:, :, 0] = 0
        g[:, :, 2] = 0
        
    
        GBthreshold = 50
    
        GB = np.where(g>GBthreshold,255,0)
    
        GBB = np.where(g>GBthreshold,1,0)

        GBB = GBB[:,:,1]
        GB2 = GB[:,:,1]


   # GREEN
        sumG2 = np.sum(GBB, axis=0)
        sumsizeG = sumG2.size
        xaxis = np.argmax(sumG2, axis=0)
        print("x: ")
        print(xaxis)


        sumG1 = np.sum(GBB, axis=1)
        sumsizeG1 = sumG1.size
        yaxis = np.argmax(sumG1, axis=0)
        print("y: ")
        print(yaxis)


        GreenFound = GB2
        dimG1 = 320
        dimG2 = 192
        indices1 = np.ones((dimG2,dimG1),dtype = np.int) * yaxis
        indices2 = np.ones((dimG2,dimG1),dtype = np.int) * xaxis
        np.put_along_axis(GreenFound,indices1,255,axis=0)
        np.put_along_axis(GreenFound,indices2,255,axis=1)
        
        
        GreenFound = GreenFound.astype(np.uint8)
        cv2.imshow('image',GreenFound)
        cv2.waitKey(1)
        cv2.imwrite('GreenFound.png',GreenFound)
        
        
        anglepwm = translate(xaxis, 0, 320, 65, 0)
        
        #if dot is gone then steer to middle
        if anglepwm == 65:
            anglepwm = 33
        
        SetAngle(anglepwm)
        
        print("Servo value: ")
        print(anglepwm)
        print("")
    


with picamera.PiCamera(
## Camera setup
        sensor_mode=6,
        resolution = (320,192),
        framerate=120
)as camera:
    with DetectBall(camera) as output:
 ## Camera warmup
        #camera.start_preview()
        time.sleep(2)
        camera.start_recording(output, format='rgb')
 ## Stop recording after 2 seconds
        camera.wait_recording(999)
        camera.stop_recording()
        
servopwm.stop()
motorpwm.stop()                    # stop PWM
# GPIO.cleanup()                     # resets GPIO ports used back to input mode
