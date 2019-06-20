import cv2
import numpy as np
from matplotlib import pyplot as plt

def main():
	img_src = cv2.imread('./color_test.png')

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
	min_red=np.array([156,43,46])
	max_red=np.array([180,255,255])

	min_red2=np.array([0,43,46])
	max_red2=np.array([5,255,255])

	min_purple=np.array([125,43,46])
	max_purple=np.array([155,255,255])

	min_yellow=np.array([26,43,46])
	max_yellow=np.array([34,255,255])

	min_blue=np.array([100,43,46])
	max_blue=np.array([124,255,255])

	min_green=np.array([35,43,46])
	max_green=np.array([77,255,255])

	min_orange=np.array([11,43,46])
	max_orange=np.array([25,255,255])

	min_black = np.array([0,  0,  0])
	max_black = np.array([180, 255, 10])

	min_white = np.array([0, 0, 70])
	max_white = np.array([180, 30, 255])

	COLORS = [
			[min_red, max_red, 'red'], [min_red2, max_red2, 'red2'],
			[min_purple, max_purple, 'purple'], [min_blue, max_blue, 'blue'],
			[min_yellow, max_yellow, 'yellow'], [min_green, max_green, 'green'],
			[min_black, max_black, 'black'], [min_white, max_white, 'white'],
			[min_orange, max_orange, 'orange']
			]

	for (color_min, color_max, name) in COLORS:
		# 使用inRange函数获取图像中目标颜色的索引
		mask=cv2.inRange(hsvImg, color_min, color_max)
		res=cv2.bitwise_and(work_img, work_img, mask=mask)
		cv2.imshow(name, res)

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