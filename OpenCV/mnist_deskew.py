import numpy as np
import cv2

image=cv2.imread('MNIST/test/3647.png')
gray=cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)## for 9 problem with 4665,8998,73,7
#I faced a problem with the deskewing and the solution suggested by @zindarod "https://stackoverflow.com/questions/51237834/deskewing-mnist-dataset-images-using-minarearect-of-opencv"
#really improved the deskewing
#gray=cv2.bitwise_not(gray)
Gblur=cv2.blur(gray,(5,5))
thresh=cv2.threshold(Gblur,0,255,cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]

#cv2.imshow("gray_thresh_blur",thresh)

#Finding Contours will be used to draw the min area rectangle

_,contours,_ = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)
cnt1 = contours[0]
cnt=cv2.convexHull(contours[0])
angle = cv2.minAreaRect(cnt)[-1]
print("Actual angle is:"+str(angle))
rect = cv2.minAreaRect(cnt)

p=np.array(rect[1])
#print(p[0])

#This gives a clearer picture of the angle made by the minAreaRect with the vertical.
#Follow up this link for understanding about the angle value retured by the function minAreaRect() :
#"https://stackoverflow.com/questions/15956124/minarearect-angles-unsure-about-the-angle-returned/16042780#16042780"
if p[0] < p[1]:
        print("Angle along the longer side:"+str(rect[-1] + 180))
        act_angle=rect[-1]+180
else:
        print("Angle along the longer side:"+str(rect[-1] + 90))
        act_angle=rect[-1]+90
#act_angle gives the angle of the minAreaRect with the vertical

if act_angle < 90:
        angle = (90 + angle)
        print("angleless than -45")
 
        # otherwise, just take the inverse of the angle to make
        # it positive
else:
        angle=act_angle-180
        print("grter than 90")
	
# rotate the image to deskew it
(h, w) = image.shape[:2]
center = (w // 2, h // 2)
M = cv2.getRotationMatrix2D(center, angle, 1.0)
rotated = cv2.warpAffine(image, M, (w, h),flags=cv2.INTER_CUBIC, borderMode=cv2.BORDER_REPLICATE)



#For drawing the minAreaRect around the image       
box = cv2.boxPoints(rect)
print(box)
box = np.int0(box)
print(box)
      

p=cv2.drawContours(thresh,[box],0,(0,0,255),1)
print("contours"+str(p))
cv2.imwrite("post/MinAreaRect9.png",p)

cv2.imwrite("post/Input_9.png", image)
cv2.imwrite('post/Deskewed_9.png', rotated)

      

