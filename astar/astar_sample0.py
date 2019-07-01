# -*- coding: utf-8 -*-
"""
Created on Sun Jun 30 19:37:49 2019

@author: Robin
"""

from astar_python.astar import Astar
import cv2 

mat = [
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
]

neighbors_8 = [(-1,-1),(0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0)]
astar = Astar(mat)

result = astar.run([0, 0], [10, 9])
print(result)


#读取一张图片，地址不能带中文
img_bg = cv2.imread("house.png")
(W,H) = img_bg.shape[:2]
print(W,H)
img_copy = img_bg.copy()
img_gray = cv2.cvtColor(img_copy, cv2.COLOR_BGR2GRAY)
thresh=cv2.threshold(img_gray,0,255,cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]

cv2.imshow('captcha', thresh)

#寻找(x,y)的8个方向上的白区域(最小块为3*3)
def findWhiteNeighbors(x,y):
    print(x,y)
    if (x < 3) or (y < 3) or ( x + 3 > W) or (y +3 > H):
        print("out of range")
        return
    if thresh[y,x] != 255:
        return    
    # 8-neighbors
    isWhiteArea = True
    for nx,ny in neighbors_8:
        #print(thresh[y+ny,x+nx])
        if thresh[y+ny,x+nx] != 255:
            isWhiteArea = False
            break
    if isWhiteArea == True:
        lt_px = x + neighbors_8[0][0]
        lt_py = y + neighbors_8[0][1]
        w, h = 2, 2  # Rectangle parameters
        cv2.rectangle(img_copy, (lt_px, lt_py), (lt_px+w, lt_py+h), (0x24, 0x7F, 0xFF), -1)  # A filled rectangle    
    #当前点周围8个点
    neighbors = [(x-2,y-2),(x,y-2),(x+2,y-2),(x+2,y),(x+2,y+2),(x,y+2),(x-2,y+2),(x-2,y)]
    for x0,y0 in neighbors:
        findWhiteNeighbors(x0,y0)

    
def on_EVENT_LBUTTONDOWN(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        #xy = "%d,%d" % (x, y)
        #print(thresh[y,x])
        if thresh[y,x] != 255:
            return
        
        findWhiteNeighbors(x,y)
        alpha = 0.75  # Transparency factor.
        # Following line overlays transparent rectangle over the image
        img_new = cv2.addWeighted(img_copy, alpha, img_bg, 1 - alpha, 0)
        
        cv2.imshow("AStar", img_new)      


        
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

cv2.setMouseCallback("AStar", on_EVENT_LBUTTONDOWN)

#显示图片，参数：（窗口标识字符串，imread读入的图像）
cv2.imshow("AStar",img_bg)

#窗口等待任意键盘按键输入,0为一直等待,其他数字为毫秒数
cv2.waitKey(0)

#销毁窗口，退出程序
cv2.destroyAllWindows()