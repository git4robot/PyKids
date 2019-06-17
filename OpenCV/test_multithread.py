import numpy as np
import sys, os
import time
import threading
import queue
import cv2

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
	
if __name__ == '__main__':

	# step-1: detect button
	
	#Create MSER object
	mser = cv2.MSER_create()
	
	# crnn network
	model = crnn.CRNN(32, 1, nclass, 256)
	if torch.cuda.is_available():
		model = model.cuda()
	print('loading pretrained model from {0}'.format(crnn_model_path))
	# 导入已经训练好的crnn模型
	model.load_state_dict(torch.load(crnn_model_path,map_location=lambda storage, loc: storage))
	
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
	
	print("Exiting Main")