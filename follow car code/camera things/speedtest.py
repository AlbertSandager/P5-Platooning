import time
import picamera
import numpy as np
import cv2

frames = 5
pic = np.empty((240,320,3),dtype=np.uint8)
def filenames():
    frame = 0
    while frame < frames:
        start = time.time()
        yield pic
        print(pic)
        cv2.imshow('image',pic)
        cv2.waitKey(0)
        frame += 1

        b = pic
    
    
# set green and red channels to 0
        b[:, :, 1] = 0
        b[:, :, 2] = 0

        g = pic
# set blue and red channels to 0
        g[:, :, 0] = 0
        g[:, :, 2] = 0

        r = pic
# set blue and green channels to 0
        r[:, :, 0] = 0
        r[:, :, 1] = 0
    
    
        GBthreshold = 220
        BBthreshold = 200
        RBthreshold = 200
    
        GB = np.where(g>GBthreshold,255,0)
        BB = np.where(b>BBthreshold,255,0)
        RB = np.where(r>RBthreshold,255,0)
    
        GBB = np.where(g>GBthreshold,1,0)
        BBB = np.where(b>BBthreshold,1,0)
        RBB = np.where(r>RBthreshold,1,0)
    
        BBB = BBB[:,:,0]
        BB2 = BB[:,:,0]
        print(BBB)
    
        sum2 = np.sum(BBB, axis=0)
        sumsize = sum2.size
        max2 = np.argmax(sum2, axis=0)
        print("Max: ")
        print(max2)
        print("Summen i max: ")
        print(sum2[max2])
    
        sum1 = np.sum(BBB, axis=1)
        sumsize1 = sum1.size
        max1 = np.argmax(sum1, axis=0)
        print("Max1: ")
        print(max1)
        print("Summen i max1: ")
        print(sum1[max1])
    
    
   # displayed = BB[sum1,sum2] = 255
        BlueFound = BB2
        dim1 = 320
        dim2 = 240
        indices1 = np.ones((dim2,dim1), dtype = np.int)*max1
    #indices1 = indices1
        indices2 = np.ones((dim2,dim1),dtype = np.int) * max2
        np.put_along_axis(BlueFound,indices1,255,axis=0)
        np.put_along_axis(BlueFound,indices2,255,axis=1)
        stop = time.time()
        print(stop-start)
        cv2.imwrite('BlueFound.png',pic)
        cv2.imshow('image',BlueFound)
        cv2.waitKey(0)

        
    



with picamera.PiCamera() as camera:
    camera.resolution = (320, 240)
    camera.framerate = 3
    #camera.start_preview()
    # Give the camera some warm-up time
    time.sleep(2)
    start = time.time()
    camera.capture_sequence(filenames(), use_video_port=True)
    finish = time.time()
print('Captured %d frames at %.2ffps' % (
    frames,
    frames / (finish - start)))