# -*- coding: utf-8 -*-
"""
Created on Sun Jun 30 19:37:49 2019

@author: Robin
"""

import numpy as np
import astar
import cv2
from PIL import Image, ImageDraw, ImageFont

H_0 = 16
W_0 = 16

img_man = cv2.imread('man.png')
img_man = cv2.resize(img_man, (W_0,H_0))
img_flag = cv2.imread('flag.png')
img_flag = cv2.resize(img_flag, (W_0,H_0))
img_wall = cv2.imread('wall.png')
#img_wall = cv2.resize(img_wall, (int(H_0 / 2), int(W_0 / 2)))
img_wall = cv2.resize(img_wall, (W_0,H_0))
#(H_0,W_0) = img_wall.shape[:2]

#读取一张图片，地址不能带中文
img_bg = cv2.imread("house.png")
(H,W) = img_bg.shape[:2]

grid_rows = int(H/H_0)
grid_cols = int(W/W_0)

img_copy = img_bg.copy()
img_gray = cv2.cvtColor(img_copy, cv2.COLOR_BGR2GRAY)
thresh=cv2.threshold(img_gray,0,255,cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]
#cv2.imshow('captcha', thresh)

nlabels, labels, stats, centroids = cv2.connectedComponentsWithStats(thresh , 4 , cv2.CV_32S)
lblareas = stats[1:,cv2.CC_STAT_AREA]
imax = max(enumerate(lblareas), key=(lambda x: x[1]))[0] + 1
'''
boundingrect = cv2.Rect(stats[imax, cv2.CC_STAT_LEFT],
					stats[imax, cv2.CC_STAT_TOP],
					stats[imax, cv2.CC_STAT_WIDTH],
					stats[imax, cv2.CC_STAT_HEIGHT])
'''
sizes = stats[:, -1]

max_label = 1
max_size = sizes[1]
for i in range(2, nlabels):
	if sizes[i] > max_size:
		max_label = i
		max_size = sizes[i]

iMaxCnt = int(H_0*W_0*0.8)
g_map = astar.Array2D(grid_cols,grid_rows)
#g_map = np.ones((grid_rows,grid_cols), dtype=np.int32)
#g_map = np.full((grid_cols, grid_rows), None)
p_from = (0,0)
p_to = (0,0)
map_res = []

work_grids = []
for r in range(0,H-H_0,H_0):
	row = int(r / H_0)
	for c in range(0,W-W_0,W_0):
		col = int(c / W_0)
		iCnt = 0
		for ro in range(0,H_0):
			for co in range(0,W_0):
				if labels[r+ro,c+co] == max_label:
					iCnt = iCnt + 1

		#if iCnt > 32: print((g_x,g_y),iCnt)
		if iCnt > iMaxCnt:
			work_grids.append((row,col))
			g_map[col][row] = 0

#print(g_map)
#print(work_grids)
'''
# black-white image for test
img2 = np.zeros(labels.shape)
img2[labels == max_label] = 255
cv2.imshow("Biggest component", img2)
cv2.imwrite("biggest.png",img2)
cv2.waitKey()
'''
mask_color = img_bg.copy()
mask_color[labels == max_label] = (0, 255, 0)
#cv2.imshow("color mask", mask_color)
#cv2.waitKey()

#cv2.fillPoly(img_copy, [stats[0]], (0x24, 0x7F, 0xFF))
alpha = 0.5
beta = 1-alpha
gamma = 0
img_add = cv2.addWeighted(mask_color, alpha, img_bg, beta, gamma)
img_add_copy = img_add.copy()

# 图像从OpenCV格式转换成PIL格式
img_PIL = Image.fromarray(cv2.cvtColor(img_add, cv2.COLOR_BGR2RGB))
font = ImageFont.truetype('fangzheng_shusong.ttf', 24)
# 文字输出位置, 输出内容
titles_list = [[210,210,u'卧室'],[480,148,u'厨房'],[490,455,u'客厅'],
			   [700,266,u'卧室'],[840,425,u'卫生间'],[790,720,u'卧室']]

draw = ImageDraw.Draw(img_PIL)
for x,y,title in titles_list:
	draw.text((x,y), title, font=font, fill=(0,0,0))
# 使用PIL中的save方法保存图片到本地
# img_PIL.save('02.jpg', 'jpeg')

# 转换回OpenCV格式
img_add_new = cv2.cvtColor(np.asarray(img_PIL),cv2.COLOR_RGB2BGR)
#绘制空白区域方格
for r,c in work_grids:
	ro = r*H_0
	co = c*W_0
	cv2.rectangle(img_add_new,(co,ro),(co+W_0,ro+H_0),(255,255,255), 1)

img_add_new_copy = img_add_new.copy()

def on_EVENT_BUTTON(event, x, y, flags, param):
	global p_from
	global p_to

	row = int(y / H_0)
	col = int(x / W_0)

	if event == cv2.EVENT_RBUTTONDOWN:
		if (row,col) not in work_grids:
			return
		if p_to[0] > 0 and p_to[1] > 0:   #clear
			w = p_to[0]*W_0
			h = p_to[1]*H_0
			img_add_new[h:h+H_0, w:w+W_0] = img_add_new_copy[h:h+H_0, w:w+W_0]
		img_add_new[row*H_0:row*H_0+H_0, col*W_0:col*W_0+W_0] = img_flag
		p_to = (col,row)
		cv2.imshow("AStar", img_add_new)
	elif event == cv2.EVENT_LBUTTONDOWN:
		if (row,col) not in work_grids:
			return
		if p_from[0] > 0 and p_from[1] > 0:   #clear
			w = p_from[0]*W_0
			h = p_from[1]*H_0
			img_add_new[h:h+H_0, w:w+W_0] = img_add_new_copy[h:h+H_0, w:w+W_0]
		img_add_new[row*H_0:row*H_0+H_0, col*W_0:col*W_0+W_0] = img_man
		p_from = (col,row)
		cv2.imshow("AStar", img_add_new)
	elif event == cv2.EVENT_RBUTTONDBLCLK:
		print("Right Button Double Click")
	elif event == cv2.EVENT_LBUTTONDBLCLK:
		print("Left Button Double Click")
	elif event == cv2.EVENT_MBUTTONDOWN:
		if (row, col) not in work_grids:
			return
		#xy = "%d,%d" % (x, y)
		#print(thresh[y,x])
		if g_map[col][row] == 0:
			img_add_new[row*H_0:row*H_0+H_0, col*W_0:col*W_0+W_0] = img_wall
			g_map[col][row] = 1
		else:
			img_add_new[row*H_0:row*H_0+H_0, col*W_0:col*W_0+W_0] = img_add_new_copy[row*H_0:row*H_0+H_0, col*W_0:col*W_0+W_0]
			g_map[col][row] = 0
		cv2.imshow("AStar", img_add_new)
		'''
		#cv2.circle(img_bg, (x, y), 1, (255, 0, 0), thickness=-1)
		#cv2.putText(img_bg, xy, (x, y), cv2.FONT_HERSHEY_PLAIN, 1.0, (0, 0, 0), thickness=1)
		#cv2.imshow("image", img_bg)
		w, h = 150, 20  # Rectangle parameters
		cv2.rectangle(img_copy, (x, y), (x+w, y+h), (0x24, 0x7F, 0xFF), -1)  # A filled rectangle
		alpha = 0.75  # Transparency factor.
		# Following line overlays transparent rectangle over the image
		img_new = cv2.addWeighted(img_copy, alpha, img_bg, 1 - alpha, 0)
		cv2.imshow("AStar", img_new)
		'''

#创建一个窗口，中文显示会出乱码
cv2.namedWindow("AStar", cv2.WINDOW_AUTOSIZE)
cv2.setMouseCallback("AStar", on_EVENT_BUTTON)

#显示图片，参数：（窗口标识字符串，imread读入的图像）
for i in range(0,3):
	cv2.imshow("AStar",img_bg)
	cv2.waitKey(400)
	cv2.imshow("AStar",img_add_new)
	cv2.waitKey(600)

for r,c in work_grids:
	ro = r*H_0
	co = c*W_0
	img_add_copy[ro:ro+H_0, co:co+W_0] = img_wall

#cv2.imshow("img_add_copy",img_add_copy)

#pts = numpy.array([[300,300],[300,340],[350,320]],numpy.int32)  #用numpy形成坐标列表
#cv2.polylines(img,[pts],True,(0,255,255),2)  #画多边形

#窗口等待任意键盘按键输入,0为一直等待,其他数字为毫秒数
cv2.waitKey(0)
while True:
	key = cv2.waitKey(0)
	#print("Key: {0}".format(key))
	if key == 13:
		print("AStar searching...")
		#执行路径查找
		if p_from[0] == 0 or p_from[1] == 0 or p_to[0] == 0 or p_to[1] == 0:
			print("start and end not setting.")
			continue
		'''	
		#map_res = astar_0.astar(g_map, p_from, p_to)
		astar = astar.Astar(g_map)
		map_res = astar.run(p_from, p_to)
		print(map_res)
		'''
		#g_map.showArray2D()
		#创建AStar对象,并设置起点为0,0终点为9,0
		aStar=astar.AStar(g_map,astar.Point(p_from[0],p_from[1]),astar.Point(p_to[0],p_to[1]))
		#开始寻路
		map_res=aStar.start()
		if map_res is None or len(map_res) == 0:
			print("Path Not Found!")
			continue
			
		if map_res is None or len(map_res) == 0:
			continue
		#map_res.reverse()
		last_p = map_res[0]
		for point in map_res:
		#for col,row in map_res[1:]:
			#print(row,col)
			'''
			row = point.y
			col = point.x
			pre_co = last_p.x*W_0
			pre_ro = last_p.y*H_0
			#img_add_new[pre_ro:pre_ro+H_0, pre_co:pre_co+W_0] = img_add_new_copy[pre_ro:pre_ro+H_0, pre_co:pre_co+W_0]
			img_add_new[row*H_0:row*H_0+H_0, col*W_0:col*W_0+W_0] = img_man
			'''
			p_center = (point.x*W_0+int(W_0/2), point.y*H_0+int(H_0/2))
			cv2.circle(img_add_new, p_center, 3, (0,0,255), thickness=-1)
			cv2.imshow("AStar", img_add_new)
			last_p = astar.Point(col,row)
			cv2.waitKey(10)
	elif key == 99:
		if map_res is None or len(map_res) == 0:
			continue
		for point in map_res[0:len(map_res)-1]:
			row = point.y*H_0
			col = point.x*W_0			
			img_add_new[row:row+H_0, col:col+W_0] = img_add_new_copy[row:row+H_0, col:col+W_0]
			cv2.imshow("AStar", img_add_new)	
	elif key == 27:
		break

#销毁窗口，退出程序
cv2.destroyAllWindows()
