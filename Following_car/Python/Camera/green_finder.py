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
        xaxis = np.argmax(sumG2, axis=0)
        print("x: ")
        print(xaxis)


        sumG1 = np.sum(GBB, axis=1)
        sumsizeG1 = sumG1.size
        yaxis = np.argmax(sumG1, axis=0)
        print("y: ")
        print(yaxis)
        print("")


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