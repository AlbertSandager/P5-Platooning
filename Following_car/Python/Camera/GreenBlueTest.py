import picamera
import numpy as np
import cv2
import time

from PIL import Image

with picamera.PiCamera() as camera:
    camera.resolution = (640, 480)
    sensor_mode=6
    camera.framerate = 24
    time.sleep(4)
    output = np.empty((480, 640, 3))
    print("Taking picture!")
    startStart = time.time()
    camera.start_recording(output,'rgb')
    print("Picture taken!")
    stopTaken = time.time()
    img = Image.fromarray(output, 'RGB')
    img.save('GRAYSCALE.png')
    img2 = cv2.imread('GRAYSCALE.png')
    b = img2.copy()
    startTaken = time.time()
    
# set green and red channels to 0
    b[:, :, 1] = 0
    b[:, :, 2] = 0

    g = img2.copy()
# set blue and red channels to 0
    g[:, :, 0] = 0
    g[:, :, 2] = 0

    r = img2.copy()
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
    GBB = GBB[:,:,1]
    GB2 = GB[:,:,1]
    print(BBB)
    

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
    dim1 = 640
    dim2 = 480
    indices1 = np.ones((dim2,dim1), dtype = np.int)*maxB1
    #indices1 = indices1
    indices2 = np.ones((dim2,dim1),dtype = np.int) * maxB2
    np.put_along_axis(BlueFound,indices1,255,axis=0)
    np.put_along_axis(BlueFound,indices2,255,axis=1)
    
    
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
    dimG1 = 640
    dimG2 = 480
    indices1 = np.ones((dimG2,dimG1), dtype = np.int)*maxG1
    #indices1 = indices1
    indices2 = np.ones((dimG2,dimG1),dtype = np.int) * maxG2
    np.put_along_axis(GreenFound,indices1,255,axis=0)
    np.put_along_axis(GreenFound,indices2,255,axis=1)
    
    stop = time.time()
    #print(sum)
    #print(len(sum))
    img.save('original.png')
    #cv2.imwrite('redscale.png',r)
    #cv2.imwrite('greenscale.png',g)
    #cv2.imwrite('bluescale.png',b)
    cv2.imwrite('GB.png',GB)
    cv2.imwrite('BB.png',BB)    
    #cv2.imwrite('RB.png',RB)
    cv2.imwrite('BlueFound.png',BlueFound)
    cv2.imwrite('GreenFound.png',GreenFound)
    print("Tid for at tage billede")
    print(stopTaken-startStart)
    print("Tid for at behandle billede")
    print(stop-startTaken)
    
