import numpy as np
import sys, os
import time
import threading
import queue
import cv2
import logging

sys.path.append(os.getcwd())

# crnn packages
import signal
import torch
from torch.autograd import Variable
import utils
import dataset
from PIL import Image
import models.crnn as crnn
import alphabets
str1 = alphabets.alphabet

import argparse
parser = argparse.ArgumentParser()
parser.add_argument('--images_path', type=str, default='test_images/test1.png', help='the path to your images')
opt = parser.parse_args()


# crnn params
# 3p6m_third_ac97p8.pth
crnn_model_path = 'trained_models/mixed_second_finetune_acc97p7.pth'
alphabet = str1
nclass = len(alphabet)+1

queueLock = threading.Lock()
workQueue = queue.Queue(10)
nameList = ['test_images/test1.png', 'test_images/test2.png', 'test_images/test3.png']


logging.basicConfig(level=logging.DEBUG,#控制台打印的日志级别
					filename='new.log',
					filemode='a',##模式，有w和a，w就是写模式，每次都会重新写日志，覆盖之前的日志
					#a是追加模式，默认如果不写的话，就是追加模式
					format='%(asctime)s - %(pathname)s[line:%(lineno)d] - %(levelname)s: %(message)s'
					#日志格式
					)

# crnn文本信息识别
def crnn_recognition(cropped_image, model):

	converter = utils.strLabelConverter(alphabet)

	image = cropped_image.convert('L')

	##
	w = int(image.size[0] / (280 * 1.0 / 160))
	transformer = dataset.resizeNormalize((w, 32))
	image = transformer(image)
	if torch.cuda.is_available():
		image = image.cuda()
	image = image.view(1, *image.size())
	image = Variable(image)

	model.eval()
	preds = model(image)

	_, preds = preds.max(2)
	preds = preds.transpose(1, 0).contiguous().view(-1)

	preds_size = Variable(torch.IntTensor([preds.size(0)]))
	sim_pred = converter.decode(preds.data, preds_size.data, raw=False)
	print('results: {0}'.format(sim_pred))
	return sim_pred

class Thread_OCR (threading.Thread):
	def __init__(self, threadID, name):
		threading.Thread.__init__(self)
		self.threadID = threadID
		self.name = name

	def run(self):
		print("Starting " + self.name)

		while True:
			queueLock.acquire()
			if not workQueue.empty():
				data = workQueue.get()
				queueLock.release()
				if data == "exit":
					break

				#print("processing %s" % (data))
				started = time.time()
				## read an image
				image = Image.open(data)
				crnn_recognition(image, model)
				finished = time.time()
				print('elapsed time: {0}'.format(finished-started))

			else:
				queueLock.release()
			time.sleep(0.05)

		print("Exiting " + self.name)

class Thread_Opera (threading.Thread):
	def __init__(self, threadID, name):
		threading.Thread.__init__(self)
		self.threadID = threadID
		self.name = name

	def Fuctime(self, s):
		if time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))>s:
			return True
		else:
			return False
	'''
	what to do when the result is not good:
	Try to change the ele_size for text_detect, smaller value
	results in a more sensitive detector in corresponding direction
	'''
	def text_detect(self, img,ele_size=(12,10)): #
		if len(img.shape)==3:
			img = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
		img_sobel = cv2.Sobel(img,cv2.CV_8U,1,0)#same as default,None,3,1,0,cv2.BORDER_DEFAULT)
		img_threshold = cv2.threshold(img_sobel,0,255,cv2.THRESH_OTSU+cv2.THRESH_BINARY)
		element = cv2.getStructuringElement(cv2.MORPH_RECT,ele_size)
		img_threshold = cv2.morphologyEx(img_threshold[1],cv2.MORPH_CLOSE,element)
		cv2.imshow("tes",img_threshold)
		cv2.waitKey(0)
		contours = cv2.findContours(img_threshold,0,1)
		Rect = [cv2.boundingRect(i) for i in contours[1] if i.shape[0]>100]
		print(Rect)
		RectP = [(int(i[0]-i[2]*0.08),int(i[1]-i[3]*0.08),int(i[0]+i[2]*1.1),int(i[1]+i[3]*1.1)) for i in Rect]

		return RectP

	def captch_ex(self, file_name):
		img = cv2.imread(file_name)
		#img_final = cv2.imread(file_name)
		img2gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
		ret, mask = cv2.threshold(img2gray, 180, 255, cv2.THRESH_BINARY)
		image_final = cv2.bitwise_and(img2gray, img2gray, mask=mask)
		ret, new_img = cv2.threshold(image_final, 180, 255, cv2.THRESH_BINARY)  # for black text , cv.THRESH_BINARY_INV
		'''
				line  8 to 12  : Remove noisy portion
		'''
		kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, (3,
															 3))  # to manipulate the orientation of dilution , large x means horizonatally dilating  more, large y means vertically dilating more
		dilated = cv2.dilate(new_img, kernel, iterations=9)  # dilate , more the iteration more the dilation
		cv2.imshow('dilated', dilated)
		cv2.waitKey()
		# for cv2.x.x
		#_, contours, hierarchy = cv2.findContours(dilated, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)  # findContours returns 3 variables for getting contours
		# for cv3.x.x comment above line and uncomment line below
		contours, hierarchy = cv2.findContours(dilated,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)

		for contour in contours:
			# get rectangle bounding contour
			[x, y, w, h] = cv2.boundingRect(contour)

			# Don't plot small false positives that aren't text
			if w < 35 and h < 35:
				continue

			# draw rectangle around contour on original image
			cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 255), 2)

			'''
			#you can crop image and send to OCR  , false detected will return no text :)
			cropped = img_final[y :y +  h , x : x + w]

			s = file_name + '/crop_' + str(index) + '.jpg'
			cv2.imwrite(s , cropped)
			index = index + 1

			'''
		# write original image with added contours to disk
		cv2.imshow('captcha_result', img)
		cv2.waitKey()
		try:
			pass
		except cv2.error as e:
			print(e)

	#he function will keep the aspect rate of the original image.
	def image_resize(self, image, width = None, height = None, inter = cv2.INTER_AREA):
		# initialize the dimensions of the image to be resized and
		# grab the image size
		dim = None
		(h, w) = image.shape[:2]

		# if both the width and height are None, then return the
		# original image
		if width is None and height is None:
			return image

		# check to see if the width is None
		if width is None:
			# calculate the ratio of the height and construct the
			# dimensions
			r = height / float(h)
			dim = (int(w * r), height)

		# otherwise, the height is None
		else:
			# calculate the ratio of the width and construct the
			# dimensions
			r = width / float(w)
			dim = (width, int(h * r))

		# resize the image
		resized = cv2.resize(image, dim, interpolation = inter)

		# return the resized image
		return resized

	def run(self):
		print("Starting " + self.name)

		while True:
			try:
				time.sleep(0.05)
				if not self.Fuctime('2019-05-18 10:28:40'):
					continue

				print("Do...")
				# part of the screen
				#im=ImageGrab.grab(bbox=(600,200,1420,780))
				#im = cv2.imread('test_images/test3.png')
				img = cv2.imread('test_images/003.png')
				#rect = self.text_detect(img)
				#print(rect)
				#self.captch_ex('test_images/002.png')

				# 转化成灰度图
				gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
				cv2.imshow('img', gray)
				cv2.waitKey(0)
				# 利用Sobel边缘检测生成二值图
				sobel = cv2.Sobel(gray, cv2.CV_8U, 1, 0, ksize=3)
				# 二值化
				ret, binary = cv2.threshold(sobel, 0, 255, cv2.THRESH_OTSU + cv2.THRESH_BINARY)
				cv2.imshow('img', binary)
				cv2.waitKey(0)
				# 膨胀、腐蚀
				element1 = cv2.getStructuringElement(cv2.MORPH_RECT, (30, 5))
				element2 = cv2.getStructuringElement(cv2.MORPH_RECT, (24, 3))

				# 膨胀一次，让轮廓突出
				dilation = cv2.dilate(binary, element2, iterations=1)
				cv2.imshow('img', dilation)
				cv2.waitKey(0)
				# 腐蚀一次，去掉细节
				erosion = cv2.erode(dilation, element1, iterations=1)
				cv2.imshow('img', erosion)
				cv2.waitKey(0)
				# 再次膨胀，让轮廓明显一些
				dilation2 = cv2.dilate(erosion, element2, iterations=2)
				cv2.imshow('img', dilation2)
				cv2.waitKey(0)
				#  查找轮廓和筛选文字区域
				region = []
				contours, hierarchy = cv2.findContours(dilation2, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
				for i in range(len(contours)):
					cnt = contours[i]
					# 计算轮廓面积，并筛选掉面积小的
					area = cv2.contourArea(cnt)
					if (area < 500):
						continue
					#print(area)
					# 找到最小的矩形

					rect = cv2.minAreaRect(cnt)
					print ("rect is: ",end='')
					print (rect)
					# box是四个点的坐标
					box = cv2.boxPoints(rect)
					box = np.int0(box)
					# 计算高和宽
					height = abs(box[0][1] - box[2][1])
					width = abs(box[0][0] - box[2][0])
					# 根据文字特征，筛选那些太细的矩形，留下扁的
					if (height > width * 1.3):
						continue

					region.append(box)

					# get the bounding rect
					x, y, w, h = cv2.boundingRect(cnt)
					#give a bit of space, because the boundingRect is not perfect
					crop = gray[y:y+h+5,x:x+w+15]

					recog_im = self.image_resize(crop,height=37)

					recog_im = cv2.bitwise_not(recog_im)

					cv2.imshow('crop',recog_im) #show the image
					cv2.waitKey(0)
					cv2.destroyAllWindows()
					#ret, recog_im = cv2.threshold(recog_im, 12, 255, cv2.THRESH_OTSU)

					#cv2图像转PIL格式图像
					pil_im = Image.fromarray(recog_im)
					started = time.time()
					crnn_recognition(pil_im, model)
					finished = time.time()
					print('elapsed time: {0}'.format(finished-started))


				# 绘制轮廓
				for box in region:
					cv2.drawContours(img, [box], 0, (0, 255, 0), 2)


				cv2.imshow('img', img)
				cv2.waitKey(0)
				cv2.destroyAllWindows()

				#for i in rect:
				#	cv2.rectangle(img,i[:2],i[2:],(0,0,255))
				#cv2.imshow("ddd", img)
				#cv2.waitKey(0)

				cv2_im = cv2.imread('test_images/test1.png')
				#cv2图像转PIL格式图像
				pil_im = Image.fromarray(cv2_im)
				started = time.time()
				#crnn_recognition(pil_im, model)
				finished = time.time()
				print('elapsed time: {0}'.format(finished-started))

				#self.box_extraction('test_images/001.png')
			except :
				print("Error: unable to start thread")
				break
			# to file
			#im.save('pim.png')
			# Notify threads it's time to exit
			break

		# Fill the queue
		queueLock.acquire()
		#for word in nameList:
		#   workQueue.put(word)
		workQueue.put("exit")
		queueLock.release()

		print("Exiting " + self.name)


def rotateImage(image, angle):
	# grab the dimensions of the image and then determine the
	# center
	(h, w) = image.shape[:2]
	(cX, cY) = (w // 2, h // 2)

	# grab the rotation matrix (applying the negative of the
	# angle to rotate clockwise), then grab the sine and cosine
	# (i.e., the rotation components of the matrix)
	M = cv2.getRotationMatrix2D((cX, cY), -angle, 1.0)
	cos = np.abs(M[0, 0])
	sin = np.abs(M[0, 1])

	# compute the new bounding dimensions of the image
	nW = int((h * sin) + (w * cos))
	nH = int((h * cos) + (w * sin))

	# adjust the rotation matrix to take into account translation
	M[0, 2] += (nW / 2) - cX
	M[1, 2] += (nH / 2) - cY

	# perform the actual rotation and return the image
	return cv2.warpAffine(image, M, (nW, nH))


def order_points(pts):
	# initialzie a list of coordinates that will be ordered
	# such that the first entry in the list is the top-left,
	# the second entry is the top-right, the third is the
	# bottom-right, and the fourth is the bottom-left
	rect = np.zeros((4, 2), dtype = "float32")

	# the top-left point will have the smallest sum, whereas
	# the bottom-right point will have the largest sum
	s = pts.sum(axis = 1)
	rect[0] = pts[np.argmin(s)]
	rect[2] = pts[np.argmax(s)]

	# now, compute the difference between the points, the
	# top-right point will have the smallest difference,
	# whereas the bottom-left will have the largest difference
	diff = np.diff(pts, axis = 1)
	rect[1] = pts[np.argmin(diff)]
	rect[3] = pts[np.argmax(diff)]

	# return the ordered coordinates
	return rect

def four_point_transform(image, pts):
	# obtain a consistent order of the points and unpack them
	# individually
	rect = order_points(pts)
	(tl, tr, br, bl) = rect

	# compute the width of the new image, which will be the
	# maximum distance between bottom-right and bottom-left
	# x-coordiates or the top-right and top-left x-coordinates
	widthA = np.sqrt(((br[0] - bl[0]) ** 2) + ((br[1] - bl[1]) ** 2))
	widthB = np.sqrt(((tr[0] - tl[0]) ** 2) + ((tr[1] - tl[1]) ** 2))
	maxWidth = max(int(widthA), int(widthB))

	# compute the height of the new image, which will be the
	# maximum distance between the top-right and bottom-right
	# y-coordinates or the top-left and bottom-left y-coordinates
	heightA = np.sqrt(((tr[0] - br[0]) ** 2) + ((tr[1] - br[1]) ** 2))
	heightB = np.sqrt(((tl[0] - bl[0]) ** 2) + ((tl[1] - bl[1]) ** 2))
	maxHeight = max(int(heightA), int(heightB))

	# now that we have the dimensions of the new image, construct
	# the set of destination points to obtain a "birds eye view",
	# (i.e. top-down view) of the image, again specifying points
	# in the top-left, top-right, bottom-right, and bottom-left
	# order
	dst = np.array([
		[0, 0],
		[maxWidth - 1, 0],
		[maxWidth - 1, maxHeight - 1],
		[0, maxHeight - 1]], dtype = "float32")

	# compute the perspective transform matrix and then apply it
	M = cv2.getPerspectiveTransform(rect, dst)
	warped = cv2.warpPerspective(image, M, (maxWidth, maxHeight))

	# return the warped image
	return warped

def getTextArea(img_src):
	# 转化成灰度图
	gray = cv2.cvtColor(img_src, cv2.COLOR_BGR2GRAY)
	#showImage('gray', gray)

	# 利用Sobel边缘检测生成二值图
	sobel = cv2.Sobel(gray, cv2.CV_8U, 1, 0, ksize=3)
	# 二值化
	ret, binary = cv2.threshold(sobel, 0, 255, cv2.THRESH_OTSU + cv2.THRESH_BINARY)
	#showImage('img', binary)

	# 膨胀、腐蚀
	element1 = cv2.getStructuringElement(cv2.MORPH_RECT, (30, 5))
	element2 = cv2.getStructuringElement(cv2.MORPH_RECT, (24, 3))

	# 膨胀一次，让轮廓突出
	dilation = cv2.dilate(binary, element2, iterations=1)
	#showImage('img', dilation)

	# 腐蚀一次，去掉细节
	erosion = cv2.erode(dilation, element1, iterations=1)
	#showImage('img', erosion)

	# 再次膨胀，让轮廓明显一些
	dilation2 = cv2.dilate(erosion, element2, iterations=2)
	#showImage('img', dilation2)

	#  查找轮廓和筛选文字区域
	region = []
	contours, hierarchy = cv2.findContours(dilation2, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
	for i in range(len(contours)):
		cnt = contours[i]
		# 计算轮廓面积，并筛选掉面积小的
		area = cv2.contourArea(cnt)
		if (area < 500):
			continue

		# 找到最小的矩形
		rect = cv2.minAreaRect(cnt)
		print ("rect is: ",end='')
		print (rect)
		# box是四个点的坐标
		box = cv2.boxPoints(rect)
		box = np.int0(box)
		# 计算高和宽
		height = abs(box[0][1] - box[2][1])
		width = abs(box[0][0] - box[2][0])
		# 根据文字特征，筛选那些太细的矩形，留下扁的
		if (height > width * 1.3):
			continue

		region.append(box)

		# get the bounding rect
		x, y, w, h = cv2.boundingRect(cnt)
		#give a bit of space, because the boundingRect is not perfect
		crop = gray[y-2:y+h+5,x-1:x+w+5]
		recog_im = resizeImage(crop,height=37)

		showImage('crop',recog_im, True, False) #show the image

		#cv2图像转PIL格式图像
		pil_im = Image.fromarray(recog_im)
		started = time.time()
		crnn_recognition(pil_im, model)
		finished = time.time()
		print('elapsed time: {0}'.format(finished-started))

	# 绘制轮廓
	for box in region:
		cv2.drawContours(img_src, [box], 0, (0, 255, 0), 2)

	showImage('img', img_src)


#he function will keep the aspect rate of the original image.
def resizeImage(image, width = None, height = None, inter = cv2.INTER_AREA):
	# initialize the dimensions of the image to be resized and
	# grab the image size
	dim = None
	(h, w) = image.shape[:2]

	# if both the width and height are None, then return the
	# original image
	if width is None and height is None:
		return image

	# check to see if the width is None
	if width is None:
		# calculate the ratio of the height and construct the
		# dimensions
		r = height / float(h)
		dim = (int(w * r), height)

	# otherwise, the height is None
	else:
		# calculate the ratio of the width and construct the
		# dimensions
		r = width / float(w)
		dim = (width, int(h * r))

	# resize the image
	resized = cv2.resize(image, dim, interpolation = inter)

	# return the resized image
	return resized

def getOKButtonPos(srcImg):
	center_point = (0,0)
	#获取mask得到白色色区域
	hsv=cv2.cvtColor(srcImg,cv2.COLOR_BGR2HSV)
	#showImage('binary', hsv, True, False)
	lower_blue=np.array([78,43,46])
	upper_blue=np.array([110,255,255])
	mask = cv2.inRange(hsv, lower_blue, upper_blue)
	#showImage('Mask', mask, True, False)
	#  查找轮廓和筛选文字区域
	region = []
	contours, hierarchy = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
	for i in range(len(contours)):
		cnt = contours[i]
		# 计算轮廓面积，并筛选掉面积小的
		area = cv2.contourArea(cnt)
		if (area < 500):
			#print("skip area < 500")
			continue

		# 找到最小的矩形
		rect = cv2.minAreaRect(cnt)
		# box是四个点的坐标
		box = cv2.boxPoints(rect)
		box = np.int0(box)
		region.append(box)
		# 4点抠图并旋转摆平
		warped = four_point_transform(srcImg, box)
		#showImage('warped',warped, True, False)
		img_gray_btn = cv2.cvtColor(warped, cv2.COLOR_BGR2GRAY)
		recog_im = cv2.bitwise_not(img_gray_btn)
		recog_im = resizeImage(recog_im,height=37)
		showImage('crop',recog_im, True, False) #show the image

		#cv2图像转PIL格式图像
		pil_im = Image.fromarray(recog_im)
		started = time.time()
		str_btn = crnn_recognition(pil_im, model)
		logging.debug('Button: '+str_btn)
		finished = time.time()
		print('elapsed time: {0}'.format(finished-started))
		x, y, w, h = cv2.boundingRect(cnt)
		center_point = (x+w/2,y+h/2)
		if  '确' in str_btn:
			print('bingo')
			return center_point

	'''
	# 绘制轮廓
	for box in region:
		cv2.drawContours(img_o, [box], 0, (0, 255, 0), 2)

	showImage('img', img_o)
	'''
	return center_point

def showImage(title,img,show=True,save=True):
	if show:
		cv2.imshow(title, img)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
	if save:
		cv2.imwrite('test_images/log/{0}_{1}.png'.format(title,time.time()),img)

if __name__ == '__main__':

	# crnn network
	model = crnn.CRNN(32, 1, nclass, 256)
	if torch.cuda.is_available():
		model = model.cuda()
	logging.debug('loading pretrained model from {0}'.format(crnn_model_path))
	# 导入已经训练好的crnn模型
	model.load_state_dict(torch.load(crnn_model_path,map_location=lambda storage, loc: storage))


	# step-1: read screenshot image
	img_screenshot = cv2.imread('test_images/001.png')
	if img_screenshot is None:
		print("image file open failed!")
		sys.exit()

	#showImage("screen", img_screenshot,False)
	# step-2: crop CAPTCHA area image
	x_c = 981
	y_c = 481
	w_c = 195
	h_c = 91
	img_c = img_screenshot[y_c:y_c+h_c, x_c:x_c+w_c]
	showImage('code', img_c)
	# analyze CAPTCHA


	# step-3: crop hint string
	x_h = 952
	y_h = 438
	w_h = 410
	h_h = 43
	img_h = img_screenshot[y_h:y_h+h_h, x_h:x_h+w_h]
	#showImage('hint', img_h)
	# 转化成灰度图
	#getTextArea(img_h)

	# step-4: crop buttons area to detect the position of OK button
	x_o = 953
	y_o = 558
	w_o = 436
	h_o = 75
	img_o = img_screenshot[y_o:y_o+h_o, x_o:x_o+w_o]
	showImage('button', img_o, False, False)
	center_point = getOKButtonPos(img_o)
	print(center_point)


	'''
	threads = []
	threadID = 1
	# Create two threads as follows
	thread = Thread_OCR(threadID, "Thread_OCR")
	thread.start()
	threads.append(thread)
	threadID += 1

	thread = Thread_Opera(threadID, "Thread_Opera")
	thread.start()
	threads.append(thread)
	threadID += 1

	# Wait for all threads to complete
	for t in threads:
		try:
			t.join()
		except KeyboardInterrupt:
			print("Error: unable to start thread")
	'''
	print("Exiting Main")