import cv2
import numpy as np
from time import sleep

#GREEN

HSV_green_min = (50, 109, 69)
HSV_green_max = (95, 241, 141)

#blue

HSV_blue_min = np.array([0, 110, 53])
HSV_blue_max = np.array([11, 196, 88])

cap = cv2.VideoCapture(0)

def find_object(im, mask, color):
    cnts, jerarquia = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

while (cap.isOpened()):
    ret, im = cap.read()

    if ret == False:
        break

    hsva = cv2.cvtColor(im, cv2.COLOR_BGR2HSV)
    hsvb = cv2.cvtColor(im, cv2.COLOR_BGR2HSV)
    mask_green = cv2.inRange(hsva, HSV_green_min, HSV_green_max)
    mask_blue = cv2.inRange(hsvb, HSV_blue_min, HSV_blue_max)

    cv2.imshow('Mask green', mask_green)
    cv2.imshow('Mask blue', mask_blue)
    cv2.imshow('Image', im)
    if cv2.waitKey(1) & 0xFF == 27:
        break

