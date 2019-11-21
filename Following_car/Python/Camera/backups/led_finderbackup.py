import cv2
import numpy as np
import picamera
import time
import picamera.array

class DetectBall(picamera.array.PiRGBAnalysis):
    
    def analyse(self, a):
        
        #r = a[:,:,2]
        #g = a[:,:,1]
        #b = a[:,:,0]
        antal = 0
        antal += 1
        #print(antal)
        #cv2.imshow('image',ImgRed)
        #cv2.waitKey(0)
        
        
    # set green and red channels to 0
        b = np.copy(a)
        b[:, :, 1] = 0
        b[:, :, 2] = 0

        g = np.copy(a)
        
    #set blue and red channels to 0
        g[:, :, 0] = 0
        g[:, :, 2] = 0
        
        r = np.copy(a)
        
    #set blue and green channels to 0
        r[:, :, 0] = 0
        r[:, :, 1] = 0
    
    
        GBthreshold = 240
        BBthreshold = 240
        RBthreshold = 240
    
        GB = np.where(g>GBthreshold,255,0)
        BB = np.where(b>BBthreshold,255,0)
        RB = np.where(r>RBthreshold,255,0)
    
        GBB = np.where(g>GBthreshold,1,0)
        BBB = np.where(b>BBthreshold,1,0)
        RBB = np.where(r>RBthreshold,1,0)
    
        BBB = BBB[:,:,0]
        BB2 = BB[:,:,0]
        GBB = GBB[:,:,1]
        GB2 = GB[:,:,1]
        #print(BBB)
    
    
    #BLUE

        sumB2 = np.sum(BBB, axis=0)
        sumsizeB = sumB2.size
        maxB2 = np.argmax(sumB2, axis=0)
        print("Max: ")
        print(maxB2)
        print("Summen i max: ")
        print(sumB2[maxB2])
    
        sumB1 = np.sum(BBB, axis=1)
        sumsizeB1 = sumB1.size
        maxB1 = np.argmax(sumB1, axis=0)
        print("Max1: ")
        print(maxB1)
        print("Summen i max1: ")
        print(sumB1[maxB1])
    
        BlueFound = BB2
        dim1 = 320
        dim2 = 192
        indices1 = np.ones((dim2,dim1), dtype = np.int)*maxB1
    #indices1 = indices1
        indices2 = np.ones((dim2,dim1),dtype = np.int) * maxB2
        np.put_along_axis(BlueFound,indices1,255,axis=0)
        np.put_along_axis(BlueFound,indices2,255,axis=1)

        BlueFound = BlueFound.astype(np.uint8)
        cv2.imshow('image',BlueFound)
        cv2.waitKey(1)
       # cv2.imwrite('BlueFound.png',BlueFound)


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
    
        GreenFound = BlueFound
        dimG1 = 320
        dimG2 = 192
        indices1 = np.ones((dimG2,dimG1), dtype = np.int)*maxG1
    #indices1 = indices1
        indices2 = np.ones((dimG2,dimG1),dtype = np.int) * maxG2
        np.put_along_axis(GreenFound,indices1,255,axis=0)
        np.put_along_axis(GreenFound,indices2,255,axis=1)
        
        #GreenFound = GreenFound.astype(np.uint8)
        #cv2.imshow('image',GreenFound)
        #cv2.waitKey(1)
        #cv2.imwrite('BlueFound.png',BlueFound)
        

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