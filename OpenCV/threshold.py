import cv2
import numpy as np

def test():
	# Test1
	img = cv2.imread('bookpage.jpg')
	retval, threshold = cv2.threshold(img, 12, 255, cv2.THRESH_BINARY)
	cv2.imshow('original',img)
	cv2.imshow('threshold',threshold)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

	# Test2
	grayscaled = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
	retval, threshold = cv2.threshold(grayscaled, 10, 255, cv2.THRESH_BINARY)
	cv2.imshow('original',img)
	cv2.imshow('threshold',threshold)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

	# Test3
	th = cv2.adaptiveThreshold(grayscaled, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 115, 1)
	cv2.imshow('original',img)
	cv2.imshow('Adaptive threshold',th)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

	# Test4
	retval2,threshold2 = cv2.threshold(grayscaled,125,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)
	cv2.imshow('original',img)
	cv2.imshow('Otsu threshold',threshold2)
	cv2.waitKey(0)
	cv2.destroyAllWindows()


def test2():
	img = cv2.imread("003.PNG")
	hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
	h,s,v = cv2.split(hsv)

	mask = cv2.inRange(hsv, (0,0,0), (180, 50, 130))
	dst1 = cv2.bitwise_and(img, img, mask=mask)

	th, threshed = cv2.threshold(v, 150, 255, cv2.THRESH_BINARY_INV)
	dst2 = cv2.bitwise_and(img, img, mask=threshed)

	th, threshed2 = cv2.threshold(s, 30, 255, cv2.THRESH_BINARY_INV)
	dst3 = cv2.bitwise_and(img, img, mask=threshed2)

	cv2.imshow("dst1.png", dst1)
	cv2.imshow("dst2.png", dst2)
	cv2.imshow("dst3.png", dst3)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

#################################################################
def test3():
	font_scale = 1.5
	font = cv2.FONT_HERSHEY_PLAIN

	# set the rectangle background to white
	rectangle_bgr = (255, 255, 255)
	# make a black image
	#img = np.zeros((500, 500))
	# set some text
	text = "Some text in a box!"
	# get the width and height of the text box
	(text_width, text_height) = cv2.getTextSize(text, font, fontScale=font_scale, thickness=1)[0]
	# set the text start position
	text_offset_x = 10
	text_offset_y = img.shape[0] - 25
	# make the coords of the box with a small padding of two pixels
	box_coords = ((text_offset_x, text_offset_y), (text_offset_x + text_width - 2, text_offset_y - text_height - 2))
	cv2.rectangle(img, box_coords[0], box_coords[1], rectangle_bgr, cv2.FILLED)
	cv2.putText(img, text, (text_offset_x, text_offset_y), font, fontScale=font_scale, color=(0, 0, 0), thickness=1)
	cv2.imshow("A box!", img)
	cv2.waitKey(0)


#########################################################################

def angle_cos(p0, p1, p2):
	d1, d2 = (p0-p1).astype('float'), (p2-p1).astype('float')
	return abs( np.dot(d1, d2) / np.sqrt( np.dot(d1, d1)*np.dot(d2, d2) ) )

def find_squares(img):
	img = cv2.GaussianBlur(img, (5, 5), 0)
	squares = []
	for gray in cv2.split(img):
		for thrs in range(0, 255, 26):
			if thrs == 0:
				bin = cv2.Canny(gray, 0, 50, apertureSize=5)
				bin = cv2.dilate(bin, None)
			else:
				_retval, bin = cv2.threshold(gray, thrs, 255, cv2.THRESH_BINARY)
			contours, _hierarchy = cv2.findContours(bin, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
			for cnt in contours:
				cnt_len = cv2.arcLength(cnt, True)
				cnt = cv2.approxPolyDP(cnt, 0.02*cnt_len, True)
				if len(cnt) == 4 and abs(cv2.contourArea(cnt)) < 1300 and abs(cv2.contourArea(cnt)) > 300 and cv2.isContourConvex(cnt):
					cnt = cnt.reshape(-1, 2)
					max_cos = np.max([angle_cos( cnt[i], cnt[(i+1) % 4], cnt[(i+2) % 4] ) for i in range(4)])
					if max_cos < 0.1:
						squares.append(cnt)
	return squares

def main():
	from glob import glob
	for fn in glob('./00*.png'):
		img = cv2.imread(fn)
		squares = find_squares(img)
		cv2.drawContours( img, squares, -1, (0, 255, 0), 3 )
		cv2.imshow('squares', img)
		ch = cv2.waitKey()
		if ch == 27:
			break

	print('Done')

def shapeDetect():
	#Create MSER object
	mser = cv2.MSER_create()

	img_org = cv2.imread('./001.png')
	
	#crop subimage you want：crop_img = img[y:y+h, x:x+w]
	x = 956
	y = 555
	w = 430
	h = 70
	img = img_org[y:y+h, x:x+w]
	img = img_org
	#Convert to gray scale
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	cv2.imshow('gray', gray)
	cv2.waitKey(0)
	
	vis = img.copy()

	#detect regions in gray scale image
	regions, _ = mser.detectRegions(gray)
	hulls = [cv2.convexHull(p.reshape(-1, 1, 2)) for p in regions]

	cv2.polylines(vis, hulls, 1, (0, 255, 0))

	cv2.imshow('img', vis)

	cv2.waitKey(0)

	mask = np.zeros((img.shape[0], img.shape[1], 1), dtype=np.uint8)

	for contour in hulls:
		cv2.drawContours(mask, [contour], -1, (255, 255, 255), -1)

	#this is used to find only text regions, remaining are ignored
	text_only = cv2.bitwise_and(img, img, mask=mask)

	cv2.imshow("text only", text_only)

	cv2.waitKey(0)


if __name__ == '__main__':
	print(__doc__)
	shapeDetect()
	#main()
	cv2.destroyAllWindows()