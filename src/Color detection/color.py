import cv2
import sys
import numpy as np

def nothing(x):
    pass

# Load in im
cap = cv2.VideoCapture(0)

ret, im = cap.read()

# Create a window
cv2.namedWindow('im')

# create trackbars for color change
cv2.createTrackbar('HMin','im',0,179,nothing) # Hue is from 0-179 for Opencv
cv2.createTrackbar('SMin','im',0,255,nothing)
cv2.createTrackbar('VMin','im',0,255,nothing)
cv2.createTrackbar('HMax','im',0,179,nothing)
cv2.createTrackbar('SMax','im',0,255,nothing)
cv2.createTrackbar('VMax','im',0,255,nothing)

# Set default value for MAX HSV trackbars.
cv2.setTrackbarPos('HMax', 'im', 179)
cv2.setTrackbarPos('SMax', 'im', 255)
cv2.setTrackbarPos('VMax', 'im', 255)

# Initialize to check if HSV min/max value changes
hMin = sMin = vMin = hMax = sMax = vMax = 0
phMin = psMin = pvMin = phMax = psMax = pvMax = 0

output = im
wait_time = 33

while(1):
    if ret == False:
        break

    # get current positions of all trackbars
    hMin = cv2.getTrackbarPos('HMin','im')
    sMin = cv2.getTrackbarPos('SMin','im')
    vMin = cv2.getTrackbarPos('VMin','im')

    hMax = cv2.getTrackbarPos('HMax','im')
    sMax = cv2.getTrackbarPos('SMax','im')
    vMax = cv2.getTrackbarPos('VMax','im')

    # Set minimum and max HSV values to display
    lower = np.array([hMin, sMin, vMin])
    upper = np.array([hMax, sMax, vMax])

    # Create HSV im and threshold into a range.
    hsv = cv2.cvtColor(im, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, lower, upper)
    output = cv2.bitwise_and(im,im, mask= mask)

    # Print if there is a change in HSV value
    if( (phMin != hMin) | (psMin != sMin) | (pvMin != vMin) | (phMax != hMax) | (psMax != sMax) | (pvMax != vMax) ):
        print("(hMin = %d , sMin = %d, vMin = %d), (hMax = %d , sMax = %d, vMax = %d)" % (hMin , sMin , vMin, hMax, sMax , vMax))
        phMin = hMin
        psMin = sMin
        pvMin = vMin
        phMax = hMax
        psMax = sMax
        pvMax = vMax

    # Display output im
    cv2.imshow('im',output)

    # Wait longer to prevent freeze for videos.
    if cv2.waitKey(wait_time) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()