import cv2
import numpy as np
import picamera
import time
import picamera.array

class DetectBall(picamera.array.PiRGBAnalysis):
    
    def analyse(self, a):

        g = np.copy(a)
        
    #set blue and red channels to 0
        g[:, :, 0] = 0
        g[:, :, 2] = 0
        
    
        GBthreshold = 200
    
        GB = np.where(g>GBthreshold,255,0)
    
        GBB = np.where(g>GBthreshold,1,0)

        GBB = GBB[:,:,1]
        GB2 = GB[:,:,1]


   # GREEN
        sumG2 = np.sum(GBB, axis=0)
        sumsizeG = sumG2.size
        maxG2 = np.argmax(sumG2, axis=0)
        print("Max: ")
        print(maxG2)
        print("Summen i max: ")
        print(sumG2[maxG2])
    
        sumG1 = np.sum(GBB, axis=1)
        sumsizeG1 = sumG1.size
        maxG1 = np.argmax(sumG1, axis=0)
        print("Max1 i green: ")
        print(maxG1)
        print("Summen i max1: ")
        print(sumG1[maxG1])
    
        GreenFound = GB2
        dimG1 = 320
        dimG2 = 192
        indices1 = np.ones((dimG2,dimG1), dtype = np.int)*maxG1
    #indices1 = indices1
        indices2 = np.ones((dimG2,dimG1),dtype = np.int) * maxG2
        np.put_along_axis(GreenFound,indices1,255,axis=0)
        np.put_along_axis(GreenFound,indices2,255,axis=1)
        
        GreenFound = GreenFound.astype(np.uint8)
        cv2.imshow('image',GreenFound)
        cv2.waitKey(1)
        cv2.imwrite('GreenFound.png',GreenFound)
        

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
        camera.wait_recording(300)
        camera.stop_recording()