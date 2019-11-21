import picamera
import numpy as np
import cv2
import time

from PIL import Image


with picamera.PiCamera() as camera:
    camera.resolution = (640, 480)
    camera.framerate = 24
    time.sleep(2)
    output = np.empty((480, 640, 3))
    print("Taking picture!")
    start = time.time()
    camera.capture(output,'rgb')
    stop = time.time()
    delta = stop-start
    print("Picture taken!")
    print(delta)
    img = Image.fromarray(output, 'RGB')
    img.save('GRAYSCALE.png')
    img2 = cv2.imread('GRAYSCALE.png')
    b = img2.copy()
    
    
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
    dim1 = 640
    dim2 = 480
    indices1 = np.ones((dim2,dim1), dtype = np.int)*max1
    #indices1 = indices1
    indices2 = np.ones((dim2,dim1),dtype = np.int) * max2
    np.put_along_axis(BlueFound,indices1,255,axis=0)
    np.put_along_axis(BlueFound,indices2,255,axis=1)
    #print(sum)
    #print(len(sum))
    img.save('original.png')
    #cv2.imwrite('redscale.png',r)
    #cv2.imwrite('greenscale.png',g)
    #cv2.imwrite('bluescale.png',b)
    #cv2.imwrite('GB.png',GB)
    cv2.imwrite('BB.png',BB)    
    #cv2.imwrite('RB.png',RB)
    cv2.imwrite('BlueFound.png',BlueFound)
    
    