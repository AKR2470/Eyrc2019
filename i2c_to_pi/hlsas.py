import time
from picamera import PiCamera
from picamera.array import PiRGBArray
import numpy as np
import cv2

def color_detect():
    low_param = [ [90, 150, 80], [50, 150, 40], [0, 130, 60], [0, 245, 115] ]
    high_param = [ [100, 255, 115], [70, 230, 90], [20, 200, 130], [30, 255, 160] ] 
    color_thresh = [95, 75, 100, 115 ]

    with PiCamera() as camera:
        camera.resolution = (320, 240)
        camera.framerate = 24
        time.sleep(2)
        for i in range(0,4):
            image = np.empty((240 * 320 * 3,), dtype=np.uint8)
            camera.capture(image, 'bgr')
            image = image.reshape((240, 320, 3))
##    cv2.circle(image,(3,62),3,(0,0,255),-1)
##    cv2.circle(image,(180,62),3,(0,0,255),-1)
##    cv2.circle(image,(3,140),3,(0,0,255),-1)
##    cv2.circle(image,(190,140),3,(0,0,255),-1)
            pts1 = np.float32([[3,62],[3,140],[180,62],[190,140]])
            pts2 = np.float32([[0,0],[0,240],[320,0],[320,240]])
            N = cv2.getPerspectiveTransform( pts1, pts2)
            dst = cv2.warpPerspective( image, N, ( 320, 240))
            lower = np.array(low_param[i])
            upper = np.array(high_param[i])
            hsv = cv2.cvtColor(dst, cv2.COLOR_BGR2HSV) 
            kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5,5))
            ero = cv2.erode(hsv,kernel,iterations = 2)# removing noise from image
            mask = cv2.inRange(ero, lower, upper)
            _, contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
            if len(contours) != 0:
                for cnt_num, cnt in  enumerate(contours):
                    M = cv2.moments(cnt)
                    cx = int(M['m10'] / (M['m00'] + 1))
                    cy = int(M['m01'] / (M['m00'] + 1))
                    a = list(dst[cx,cy])
                    print(a)
                    cv2.drawContours(dst, contours, cnt_num, 4, 24)
                    cv2.circle(dst, (cx, cy), 3, (0, 0, 0), -1)
                    cv2.putText(dst, "({},{})".format(cx, cy), (cx, cy), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1, cv2.LINE_AA)
               
                if ( a[0] >= color_thresh[i] and a[1] < color_thresh[i] and a[2] < color_thresh[i]):
                    color = 3
                elif ( a[1] >= color_thresh[i] and a[0] < color_thresh[i] and a[2] < color_thresh[i]):   
                    color = 2
                elif ( a[2] >= color_thresh[i] and a[0] < color_thresh[i] and a[1] < color_thresh[i]):
                    color = 1
                elif ( a[2] >= color_thresh[i] and a[1] >= color_thresh[i] and a[0] < color_thresh[i]):
                    color = 4
                else:
                    color = 0
    return color    
    #print(color) 
            #cv2.imshow("mask",mask)
    #cv2.waitKey(0)
    #cv2.destroyAllWindows()


##if __name__ == "__main__":
##    print(color_detect())

