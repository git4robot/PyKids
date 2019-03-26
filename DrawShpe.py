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

class JamesPoint:
    jx = 0.0
    jy = 0.0
    
    def __init__(self, x, y):
        self.jx = x
        self.jy = y

class Shape:
    pass



class Rectangle(Shape):
    topLeft = JamesPoint(0.0,0.0)
    topRight = JamesPoint(0.0,0.0)

    width = 0.0
    height = 0.0
    
    def __init__(self, startpoint, wid, hei):
        print("__init__ Enter...")
        self.topLeft = startpoint
        self.width = wid
        self.height = hei
        self.topRight.jx = self.topLeft.jx + self.width
        self.topRight.jy = self.topLeft.jy + self.height
        
    def __del__(self):  
        print("__del__ Enter...")
        
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
    
    def Draw(self):
        t = turtle.Pen()
        t.goto(self.topLeft.jx,self.topLeft.jy)
        t.goto(self.topRight.jx,self.topRight.jy)
        
        turtle.done()


if __name__ == '__main__':
    startp = JamesPoint(10.0,10.0)
    myRect = Rectangle(startp, 10.0, 5.0)
    print(myRect.Perimeter())
    print(myRect.Area())
    center = myRect.Center()
    print(center.jx,center.jy)
    myRect.Draw()

 
