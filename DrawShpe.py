# -*- coding: utf-8 -*-
"""
Created on Tue Mar 26 20:45:15 2019

@author: Robot
"""

# -*- coding: utf-8 -*-
"""
Created on Wed Mar 20 20:55:35 2019

@author: Robot
"""

import turtle
import math

class JamesPoint:
    jx = 0.0
    jy = 0.0
    
    def __init__(self, x, y):
        self.jx = x
        self.jy = y

class Shape:
    pass

#设置turtle的窗口为全屏幕显示
turtle.Screen().setup(width=1.0, height=1.0, startx=None, starty=None)
t = turtle.Pen()
t.color(1,0,1)

class Rectangle(Shape):
    topLeft = JamesPoint(0.0,0.0)
    topRight = JamesPoint(0.0,0.0)
    bottomLeft = JamesPoint(0.0,0.0)
    bottomRight = JamesPoint(0.0,0.0)
    
    width = 0.0
    height = 0.0
    
    def __init__(self, startpoint, wid, hei):
        print("__init__ Enter...")
        self.topLeft = startpoint
        self.width = wid
        self.height = hei
        self.topRight.jx = self.topLeft.jx + self.width
        self.topRight.jy = self.topLeft.jy
        self.bottomLeft.jx = self.topLeft.jx
        self.bottomLeft.jy = self.topLeft.jy + self.height
        self.bottomRight.jx = self.topRight.jx
        self.bottomRight.jy = self.topLeft.jy + self.height

        
    def Perimeter(self):
        print("Perimeter Enter...")
        return (self.width + self.height) * 2.0
        
    def Area(self):
        print("Area Enter...")
        return self.width * self.height

    def Center(self):
        print("Center Enter...")
        newx = self.topLeft.jx + self.width / 2.0
        newy = self.topLeft.jy + self.height / 2.0
        return JamesPoint(newx,newy)
    
    def Draw_(self):
        self.Draw(self.topLeft,self.bottomRight)
        
    def Draw(self,tLeft,bRight):
        t.penup()   #抬起画笔，把画笔移动到起点
        t.goto(tLeft.jx,tLeft.jy)
        t.pendown() #放下画笔开始画矩形
        
        t.goto(bRight.jx,tLeft.jy)
        t.goto(bRight.jx,bRight.jy)
        t.goto(tLeft.jx,bRight.jy)
        t.goto(tLeft.jx,tLeft.jy)  
        
    def Move(self,end_point):
        t.penup()
        #根据提供的中心点计算起点位置
        from_point = JamesPoint(end_point.jx - self.width/2, end_point.jy - self.height/2)
        t.goto(from_point.jx,from_point.jy)
        t.pendown()
        
        t.forward(self.width)
        t.right(90)
        t.forward(self.height)
        t.right(90)
        t.forward(self.width)
        t.right(90)
        t.forward(self.height)
        

class Square(Rectangle):
    def __init__(self, startpoint, side_length):
        print("__init__ Enter...")
        self.topLeft = startpoint
        self.width = side_length
        self.height = side_length
        self.topRight.jx = self.topLeft.jx + self.width
        self.topRight.jy = self.topLeft.jy
        self.bottomLeft.jx = self.topLeft.jx
        self.bottomLeft.jy = self.topLeft.jy + self.height
        self.bottomRight.jx = self.topRight.jx
        self.bottomRight.jy = self.topLeft.jy + self.height


class Circle(Shape):
    center = JamesPoint(0.0,0.0)
    radius = 0.0
    
    def __init__(self,startpoint,radius):
        print("__init__ Enter...")
        self.center = startpoint
        self.radius = radius
    
    def Perimeter(self):
        print("Perimeter Enter...")
        return math.pi * self.radius * 2.0
        
    def Area(self):
        print("Area Enter...")
        return math.pi * self.radius ** 2
    
    def Draw(self):
        t.penup()   #抬起画笔，把画笔移动到起点
        t.goto(self.center.jx,self.center.jy)
        t.pendown()
        t.circle(self.radius)
        
if __name__ == '__main__':
    startp = JamesPoint(10.0,10.0)
    '''
    myRect = Rectangle(startp, 100.0, 50.0)
    print(myRect.Perimeter())
    print(myRect.Area())
    center = myRect.Center()
    print(center.jx,center.jy)
    myRect.Draw()
    '''
    '''
    mySqua = Square(startp,75.0)
    print(mySqua.Perimeter())
    print(mySqua.Area())
    center = mySqua.Center()
    print(center.jx,center.jy)
    #mySqua.Draw_()
    mySqua.Move(JamesPoint(.0,.0))
    mySqua.Move(JamesPoint(-300.0,300.0))
    
    mySqua.Move(JamesPoint(300.0,300.0))
    
    mySqua.Move(JamesPoint(300.0,-300.0))
    
    mySqua.Move(JamesPoint(-300.0,-300.0))
    '''
    mycirc = Circle(startp,75)
    print(mycirc.Perimeter())
    print(mycirc.Area())
    print(startp.jx,startp.jy)
    mycirc.Draw()
    turtle.done()
