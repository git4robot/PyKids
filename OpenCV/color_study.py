'''
# RGB: https://www.jianshu.com/p/25712f48a354

'''

import cv2
import numpy as np
from sklearn.cluster import KMeans
from collections import Counter
from matplotlib import pyplot as plt

def get_dominant_color(image, k=4, image_processing_size = None):
	"""
	takes an image as input
	returns the dominant color of the image as a list

	dominant color is found by running k means on the
	pixels & returning the centroid of the largest cluster

	processing time is sped up by working with a smaller image;
	this resizing can be done with the image_processing_size param
	which takes a tuple of image dims as input

	>>> get_dominant_color(my_image, k=4, image_processing_size = (25, 25))
	[56.2423442, 34.0834233, 70.1234123]
	"""
	#resize image if new dims provided
	if image_processing_size is not None:
		image = cv2.resize(image, image_processing_size,
							interpolation = cv2.INTER_AREA)

	#reshape the image to be a list of pixels
	image = image.reshape((image.shape[0] * image.shape[1], 3))

	#cluster and assign labels to the pixels
	clt = KMeans(n_clusters = k)
	labels = clt.fit_predict(image)

	#count labels to find most popular
	label_counts = Counter(labels)

	#subset out most popular centroid
	dominant_color = clt.cluster_centers_[label_counts.most_common(1)[0][0]]

	return list(dominant_color)

def main():
	img_src = cv2.imread(r'./test001.png')

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

	height = hsvImg.shape[0]
	width = hsvImg.shape[1]
	#收集图片不同像素
	colorsMap = {}
	for row in range(height):
		for col in range(width):
			pxH = hsvImg[row,col,0]
			if pxH != 0:
				if pxH not in colorsMap:
					colorsMap[pxH] = [(row, col)]
				colorsMap[pxH].append((row,col))

	#print(colorsMap.keys())

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

	min_cyan = np.array([78, 43, 46])
	max_cyan = np.array([99,255,255])

	min_black = np.array([0,  0,  0])
	max_black = np.array([180, 255, 10])

	min_white = np.array([0, 0, 70])
	max_white = np.array([180, 30, 255])

	COLORS = [
			[min_red, max_red, 'red'], [min_red2, max_red2, 'red2'],
			 [min_green, max_green, 'green'], [min_blue, max_blue, 'blue'],
			[min_yellow, max_yellow, 'yellow'],[min_purple, max_purple, 'purple'],
			[min_orange, max_orange, 'orange'],[min_black, max_black, 'black'],
			[min_white, max_white, 'white'], [min_cyan, max_cyan, 'cyan']
			]

	for (color_min, color_max, name) in COLORS:
		# 使用inRange函数获取图像中目标颜色的索引
		mask=cv2.inRange(hsvImg, color_min, color_max)
		res=cv2.bitwise_and(work_img, work_img, mask=mask)
		cv2.imshow(name, res)
		gray = cv2.cvtColor(res, cv2.COLOR_BGR2GRAY)
		binary = cv2.threshold(gray,0,255,cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]

		cnts = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
		if cnts is None or len(cnts) == 0:
			continue
		cnt_max = sorted(cnts, key=cv2.contourArea)[-1]
		if cnt_max is None:
			continue
		## (4) Crop and save it
		x,y,w,h = cv2.boundingRect(cnt_max)
		#print(x,y,w,h)
		if w < (h*1.3):
			continue
		print(name)



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