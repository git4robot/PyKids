import cv2
import numpy as np
from matplotlib import pyplot as plt

def main():
	img_src = cv2.imread('./colors_circles.png')

	#plt.imshow(img_src, cmap = 'gray', interpolation = 'bicubic')
	#plt.xticks([]), plt.yticks([])  # to hide tick values on X and Y axis
	#plt.show()

	cv2.namedWindow('img_src', cv2.WINDOW_AUTOSIZE)
	#cv2.resizeWindow("img_src", 300,300)
	cv2.imshow('img_src', img_src)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

	work_img = img_src.copy()
	hsvImg = cv2.cvtColor(work_img, cv2.COLOR_BGR2HSV)   #BGR not RGB
	cv2.imshow('hsvImg', hsvImg)
	cv2.waitKey(0)
	cv2.destroyAllWindows()
	# 分别设置HSV颜色空间中，红色、黄色、蓝色、绿色的阈值
	lower_red=np.array([156,43,46])
	upper_red=np.array([180,255,255])
	lower_red2=np.array([0,43,46])
	upper_red2=np.array([5,255,255])
	lower_purple=np.array([125,43,46])
	upper_purple=np.array([155,255,255])
	lower_yellow=np.array([26,43,46])
	upper_yellow=np.array([34,255,255])
	lower_blue=np.array([100,43,46])
	upper_blue=np.array([124,255,255])
	lower_green=np.array([35,43,46])
	upper_green=np.array([77,255,255])
	lower_orange=np.array([11,43,46])
	upper_orange=np.array([25,255,255])
	# 使用inRange函数获取图像中目标颜色的索引
	mask_red=cv2.inRange(hsvImg,lower_red,upper_red)
	mask_red2=cv2.inRange(hsvImg,lower_red2,upper_red2)
	mask_blue=cv2.inRange(hsvImg,lower_blue,upper_blue)
	mask_green=cv2.inRange(hsvImg,lower_green,upper_green)
	mask_yellow=cv2.inRange(hsvImg,lower_yellow,upper_yellow)
	mask_purple=cv2.inRange(hsvImg,lower_purple,upper_purple)
	mask_orange=cv2.inRange(hsvImg,lower_orange,upper_orange)
	res = cv2.bitwise_and(work_img, work_img, mask=mask_red)
	cv2.imshow('mask_red', res)
	res = cv2.bitwise_and(work_img, work_img, mask=mask_red2)
	cv2.imshow('mask_red2', res)
	res = cv2.bitwise_and(work_img, work_img, mask=mask_blue)
	cv2.imshow('mask_blue', res)
	res = cv2.bitwise_and(work_img, work_img, mask=mask_green)
	cv2.imshow('mask_green', res)
	res = cv2.bitwise_and(work_img, work_img, mask=mask_yellow)
	cv2.imshow('mask_yellow', res)
	res = cv2.bitwise_and(work_img, work_img, mask=mask_purple)
	cv2.imshow('mask_purple', res)
	res = cv2.bitwise_and(work_img, work_img, mask=mask_orange)
	cv2.imshow('upper_orange', res)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

	'''
	height = img_src.shape[0]
	width = img_src.shape[1]
	channels = img_src.shape[2]

	for row in range(height):
		for col in range(width):
			for c in range(channels):
				print(hsvImg[row, col, c],end=' ')
			print()
	'''

	print('Done')

if __name__ == '__main__':
	print(__doc__)
	main()
	cv2.destroyAllWindows()