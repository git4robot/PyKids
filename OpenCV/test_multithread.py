import numpy as np
import sys, os
import time
import threading
import queue
import cv2
import logging
import pyscreenshot as ImageGrab
from ahk import AHK

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

# crnn params
# 3p6m_third_ac97p8.pth
crnn_model_path = 'trained_models/mixed_second_finetune_acc97p7.pth'
alphabet = str1
nclass = len(alphabet)+1

queueLock = threading.Lock()
workQueue = queue.Queue(10)
nameList = ['test_images/test1.png', 'test_images/test2.png', 'test_images/test3.png']


cur_path = os.path.dirname(os.path.abspath(sys.argv[0]))

logging.basicConfig(level=logging.DEBUG,#控制台打印的日志级别
					#a是追加模式，默认如果不写的话，就是追加模式
					format='%(asctime)s - %(pathname)s[line:%(lineno)d] - %(levelname)s: %(message)s',
					#日志格式
					handlers=[logging.FileHandler(cur_path+'new.log'), logging.StreamHandler()]
					)

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

COLORS_0 = {
		'red':(min_red, max_red),'red2':(min_red2, max_red2),'green':(min_green, max_green),
		'blue':(min_blue, max_blue),'yellow':(min_yellow, max_yellow),'purple':(min_purple, max_purple),
		'orange':(min_orange, max_orange),'black':(min_black, max_black),'white':(min_white, max_white),
		'cyan':(min_cyan, max_cyan)
		}
COLORS = [
		[min_red, max_red, 'red'], [min_red2, max_red2, 'red2'],
		 [min_green, max_green, 'green'], [min_blue, max_blue, 'blue'],
		[min_yellow, max_yellow, 'yellow'],[min_purple, max_purple, 'purple'],
		[min_orange, max_orange, 'orange'],[min_black, max_black, 'black'],
		[min_white, max_white, 'white'], [min_cyan, max_cyan, 'cyan']
		]
sColorKey = {'红':'red','绿':'green','蓝':'blue','黄':'yellow','紫':'purple','橙':'orange','黑':'black','白':'white'}

cur_dir = 0

region_dbg = []

x_h = 5
y_h = 91
w_h = 390
h_h = 60

x_c = 5
y_c = 120
w_c = 195
h_c = 91

x_o = 5
y_o = 220
w_o = 436
h_o = 75

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

def showImage(title,img,show=True,save=True):
	if show:
		cv2.imshow(title, img)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
	if save:
		cv2.imwrite('test_images/log/{0}/{1}_{2}.png'.format(cur_dir,title,int(time.time())),img)

def recogText(srcImg, model):
	if srcImg is None:
		return ''
	recog_im = resizeImage(srcImg,height=37)
	#showImage('crop',recog_im, True, False) #show the image

	#cv2图像转PIL格式图像
	pil_im = Image.fromarray(recog_im)
	str_btn = crnn_recognition(pil_im, model)

	return str_btn

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

def getBlackText(srcImgBin):
	newImg = srcImgBin.copy()
	white = []  # 记录每一列的白色像素总和
	black = []  # 记录每一列的黑色像素总和
	height = srcImgBin.shape[0]
	width = srcImgBin.shape[1]
	print(width, height)
	white_max = 0   # 仅保存每列，取列中白色最多的像素总数
	black_max = 0   # 仅保存每列，取列中黑色最多的像素总数

	# 循环计算每一列的黑白色像素总和
	for i in range(width):
		w_count = 0	 # 这一列白色总数
		b_count = 0	 # 这一列黑色总数
		for j in range(height):
			if srcImgBin[j][i] == 255:
				w_count += 1
			else:
				b_count += 1
		white_max = max(white_max, w_count)
		black_max = max(black_max, b_count)
		white.append(w_count)
		black.append(b_count)


	# False表示白底黑字；True表示黑底白字
	isWhiteTxt = black_max > white_max
	if isWhiteTxt:
		print("black...")
		newImg = cv2.bitwise_not(newImg)
	return newImg

def getTextArea(img_src, model):
	hint_txt = ""
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
	contours, hierarchy = cv2.findContours(dilation2, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
	for i in range(len(contours)):
		cnt = contours[i]
		# 计算轮廓面积，并筛选掉面积小的
		area = cv2.contourArea(cnt)
		if (area < 500):
			continue

		# 找到最小的矩形
		rect = cv2.minAreaRect(cnt)
		# box是四个点的坐标
		box = cv2.boxPoints(rect)
		box = np.int0(box)
		# 计算高和宽
		height = abs(box[0][1] - box[2][1])
		width = abs(box[0][0] - box[2][0])
		# 根据文字特征，筛选那些太细的矩形，留下扁的
		if (height > width * 1.3):
			continue

		box = box + (x_h,y_h)
		region_dbg.append(box)

		# get the bounding rect
		x, y, w, h = cv2.boundingRect(cnt)
		#give a bit of space, because the boundingRect is not perfect
		crop = gray[y:y+h,x:x+w]
		hint_txt += recogText(crop, model)

	return hint_txt

def getOKButtonPos(srcImg, model):
	center_point = (0,0)
	#获取mask得到白色色区域
	hsv=cv2.cvtColor(srcImg,cv2.COLOR_BGR2HSV)
	#showImage('binary', hsv, True, False)
	lower_blue=np.array([78,43,46])
	upper_blue=np.array([110,255,255])
	mask = cv2.inRange(hsv, lower_blue, upper_blue)
	#showImage('Mask', mask, True, False)
	#  查找轮廓和筛选文字区域
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
		# 计算高和宽
		height = abs(box[0][1] - box[2][1])
		width = abs(box[0][0] - box[2][0])
		# 根据文字特征，筛选那些太细的矩形，留下扁的
		if width > 210 or height < 10:
			continue

		# 4点抠图并旋转摆平
		warped = four_point_transform(srcImg, box)
		#绘制轮廓用
		box = box + (x_o,y_o)
		region_dbg.append(box)

		#showImage('warped',warped, True, False)
		img_gray_btn = cv2.cvtColor(warped, cv2.COLOR_BGR2GRAY)
		recog_im = cv2.bitwise_not(img_gray_btn)
		str_btn = recogText(recog_im, model)
		logging.debug(u'Button文字: %s' % str_btn)
		x, y, w, h = cv2.boundingRect(cnt)
		center_point = (x+w/2,y+h/2)
		center_point = np.int0(center_point)
		if  '确' in str_btn:
			logging.debug('bingo:({0},{1})'.format(center_point[0],center_point[1]))
			#return center_point
			break

	return center_point

def getCaptcha(srcImg, strHint):
	strCode = ''

	gray = cv2.cvtColor(srcImg, cv2.COLOR_BGR2GRAY)
	thresh=cv2.threshold(gray,0,255,cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)[1]
	#showImage('captcha', thresh, True, False)

	pixelpoints = cv2.findNonZero(thresh)
	x,y,w,h = cv2.boundingRect(pixelpoints)
	#数字图片上下半分
	h_half = int(h/2)
	digit_img_1 = thresh[y:y+h_half, x:x+w]
	digit_img_2 = thresh[y+h_half:y+h, x:x+w]

	digit_img = srcImg[y:y+h, x:x+w]
	rect = cv2.minAreaRect(pixelpoints)
	box = cv2.boxPoints(rect)
	box = np.int0(box)
	box = box + (x_c,y_c)
	region_dbg.append(box)

	cv2.imshow("00", thresh)
	cv2.imshow('01', digit_img)

	new_img = getBlackText(digit_img_1)
	str_btn = recogText(new_img, model)
	cv2.imshow("20", new_img)

	new_img = getBlackText(digit_img_2)
	str_btn = recogText(new_img, model)
	cv2.imshow("21", new_img)
	cv2.waitKey(0)



	## (3) Find the max-area contour
	cnts = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
	cnt_max = sorted(cnts, key=cv2.contourArea)[-1]

	## (4) Crop and save it
	x,y,w,h = cv2.boundingRect(cnt_max)
	#print(x,y,w,h)
	dst = srcImg[y:y+h, x:x+w]

	work_img = dst.copy()
	showImage('code0', dst, False, True)

	hsvImg = cv2.cvtColor(work_img, cv2.COLOR_BGR2HSV)   #BGR not RGB

	imode = -1

	name = 'red2'


	for (color_min, color_max, name) in COLORS:
		# 使用inRange函数获取图像中目标颜色的索引
		mask=cv2.inRange(hsvImg, color_min, color_max)
		res=cv2.bitwise_and(work_img, work_img, mask=mask)
		gray = cv2.cvtColor(res, cv2.COLOR_BGR2GRAY)
		binary = cv2.threshold(gray,0,255,cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]
		#showImage("00"+name, binary, False, True)
		cv2.imshow("00"+name, gray)
		#cv2.imshow("11"+name, binary)

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
		dst = work_img[y:y+h, x:x+w]
		cv2.imshow(name, dst)

		w = w - 4
		h = h - 4
		x = x + 2
		y = y + 2
		dst = work_img[y:y+h, x:x+w]
		showImage('code1', dst, False, True)
		strCode = recogText(dst, model)

	cv2.waitKey(0)
	cv2.destroyAllWindows()

	'''
	# 使用inRange函数获取图像中目标颜色的索引
	mask=cv2.inRange(hsvImg, color_min, color_max)
	res=cv2.bitwise_and(work_img, work_img, mask=mask)
	showImage(name,res, False, True)

	gray = cv2.cvtColor(res, cv2.COLOR_BGR2GRAY)
	binary = cv2.threshold(gray,0,255,cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]

	cnts = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
	if cnts is None or len(cnts) == 0:
		return ""
	cnt_max = sorted(cnts, key=cv2.contourArea)[-1]
	if cnt_max is None:
		return ""
	## (4) Crop and save it
	x,y,w,h = cv2.boundingRect(cnt_max)
	#print(x,y,w,h)
	if w < (h*1.3):
		return ""
	print(name)
	w = w - 4
	h = h - 4
	x = x + 2
	y = y + 2
	dst = work_img[y:y+h, x:x+w]
	showImage('code1', dst, False, True)
	strCode = recogText(dst, model)

	cv2.imshow(name, dst)
	cv2.waitKey(0)

	cv2.destroyAllWindows()
	'''

	return strCode


if __name__ == '__main__':

	ahk = AHK()

	#time.sleep(2)

	# crnn network
	model = crnn.CRNN(32, 1, nclass, 256)
	if torch.cuda.is_available():
		model = model.cuda()
	logging.debug('loading pretrained model from {0}'.format(crnn_model_path))
	# 导入已经训练好的crnn模型
	model.load_state_dict(torch.load(crnn_model_path,map_location=lambda storage, loc: storage))

	while True:
		'''
		cur_dir = cur_dir+1
		newpath = r'./test_images/log/{0}'.format(cur_dir)
		if not os.path.exists(newpath):
			os.makedirs(newpath)
		else:
			continue
		'''
		cur_dir = 18
		region_dbg.clear()

		screenshot = ImageGrab.grab(bbox=(517, 110,1418, 814))
		# to file
		#screenshot.save('test_images/log/{0}/000.png'.format(cur_dir))

		# step-0: AHK执行，获取屏幕
		#ahk.double_click(1205, 423)  #+价输入框
		#输入自定义数值+400
		#ahk.send_input('400')
		ahk.click(1327, 421)
		#点击按钮弹出对话框
		ahk.click(1325, 534)

		#time.sleep(0.4)

		p0_x = 950
		p0_y = 358
		p1_x = 1370
		p1_y = 640
		screenshot = ImageGrab.grab(bbox=(p0_x, p0_y, p1_x, p1_y))
		# to file
		#screenshot.save('test_images/log/{0}/001.png'.format(cur_dir))

		started = time.time()

		# step-1: read screenshot image
		img_screenshot = cv2.imread('test_images/005.png')
		#img_screenshot = cv2.imread('test_images/log/{0}/001.png'.format(cur_dir))
		if img_screenshot is None:
			print("image file open failed!")
			sys.exit()

		# step-2: crop hint string
		#cv2.rectangle(img_screenshot, (x_h,y_h), (x_h+w_h,y_h+h_h), (0,255,0), 2)
		#showImage('hint', img_screenshot, True, False)
		img_h = img_screenshot[y_h:y_h+h_h, x_h:x_h+w_h]
		showImage('hint', img_h, False, True)
		# 转化成灰度图
		txt_hint = getTextArea(img_h, model)
		logging.debug(u"提示文字：%s", txt_hint)
		if len(txt_hint) < 1:
			time.sleep(2)
			break

		# step-3: crop CAPTCHA area image
		img_c = img_screenshot[y_c:y_c+h_c, x_c:x_c+w_c]
		showImage('code', img_c, False, True)
		# analyze CAPTCHA
		str_code = getCaptcha(img_c, txt_hint)
		logging.debug(u"代码：%s", str_code)

		# step-4: crop buttons area to detect the position of OK button
		img_o = img_screenshot[y_o:y_o+h_o, x_o:x_o+w_o]
		#showImage('button', img_o, False, True)
		center_point = getOKButtonPos(img_o, model)
		ok_btn_pos = (p0_x+x_o+center_point[0], p0_y+y_o+center_point[1])
		logging.debug("OK button position:(%d,%d)",ok_btn_pos[0],ok_btn_pos[1])

		finished = time.time()
		logging.debug('Total elapsed: {0}'.format(finished-started))
		'''
		# step-5: AHK 执行
		#点击输入框，准备输入
		ahk.click(1234, 536)
		#输入数字
		ahk.send_input(str_code)
		#最后确认
		ahk.click(ok_btn_pos)
		'''

		# 绘制轮廓
		cv2.circle(img_screenshot, ok_btn_pos,3, (0, 0, 255),-1)
		for box in region_dbg:
			cv2.drawContours(img_screenshot, [box], 0, (0, 255, 0), 2)
		showImage('debug', img_screenshot, False, True)

		print("do next>")

		#time.sleep(1)
		break

	print("Exiting Main")