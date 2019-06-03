# -*- coding: utf-8 -*-
"""
Created on Wed Jun 1 10:45:00 2019

@author: Robin
"""

'''A module to draw spirals on the turtle screen'''
import turtle #引入turtle模块
import random #引入random模块
t = turtle.Pen()
turtle.bgcolor('black') #将背景颜色设为黑色
t.speed(0) #将速度设为最快(1-10 (从慢到快，有动画)、0 (无动画))

def sp1(): #彩色螺旋图形1
    colors = ['red','blue','purple','pink','orange','yellow']
    for x in range(360):
        t.pencolor(colors[x % 6]) #选择颜色
        t.width(x / 100 + 1)
        t.forward(x)
        t.left(59)
    turtle.done()
    
def sp2(): #彩色螺旋图形2
    colors = ["red", "gray","yellow","blue","purple","green","orange","white","yellow"]
    sides = int(turtle.numinput('Title','How many sides do you want(1 - 8)?',8,1,8)) #范围在1到8，默认8
    '''
    sides -- How many sides does the spiral have
    '''
    for x in range(360):
        t.pencolor(colors[x % sides]) #选择颜色
        t.forward(x * 3 / sides + x)
        t.left(360 / sides + 1)
        t.width(x * sides / 200) #修改笔的粗细，增加宽度或厚度
    turtle.done()
    
def sp3(): #彩色螺旋图形3
    colors = ['red','blue','purple','pink','orange','yellow']
    sides = int(turtle.numinput('Title','How many sides do you want(2 - 6)?',5,2,6)) #范围在2到6，默认5
    '''
    sides -- How many sides does the spiral have
    '''
    for x in range(360):
        t.pencolor(colors[x % sides]) #选择颜色
        t.forward(x * 3 / sides + x)
        t.left(360 / sides + 1)
        t.width(x * sides / 200) #修改笔的粗细，增加宽度或厚度
    turtle.done()
    
def rsp(num1 = 25): #随机螺旋图形
    '''
    num1 -- How many random spirals do you want
    xx/yy -- Where is the spiral
    size -- How long is the spiral
    '''
    colors = ['red','blue','purple','pink','orange','yellow','gray','white']
    for y in range(num1):
        t.pencolor(random.choice(colors)) #选择随机的颜色
        size = random.randint(10,40) #选择随机的边长
        xx = random.randrange(-turtle.window_width() // 2,turtle.window_width() // 2) #选择地点画螺旋线
        yy = random.randrange(-turtle.window_height() // 2,turtle.window_height() // 2) #选择地点画螺旋线
        
        t.penup()
        t.setpos(xx,yy)
        t.pendown()
        for z in range(size):
            t.forward(z * 2)
            t.left(91)
    turtle.done()

def ksp(num1 = 20): #万花筒
    '''
    num1 -- How many kaleidoscopes do you want(num1 * 4)
    size -- How long is the spiral
    sides -- How many sides does the spiral have
    thick -- The turtle_pen's thick 
    x/y -- Where is the spiral
    angle -- The turtle_pen's heading
    '''
    colors = ["red", "yellow", "blue", "green", "orange", "purple", "white", "gray"]
    for n in range(num1):
        t.pencolor(random.choice(colors))
        size = random.randint(15,30)
        sides = random.randint(4,7)
        thick = random.randint(1,3)
        x = random.randrange(size,turtle.window_width()//2)
        y = random.randrange(size,turtle.window_height()//2)
        angle = t.heading()
        #第一个螺旋线
        t.penup()
        t.setpos(x,y)
        t.pendown()
        t.width(thick)
        t.setheading(angle)
        for m in range(size):
            t.forward(m*2)
            t.left(360 / sides + 1)
            #第二个螺旋线
        t.penup()
        t.setpos(-x,y)
        t.pendown()
        t.width(thick)
        t.setheading(180 - angle)
        for m in range(size):
            t.forward(m*2)
            t.left(360 / sides + 1)
            #第三个螺旋线
        t.penup()
        t.setpos(-x,-y)
        t.pendown()
        t.width(thick)
        t.setheading(angle - 180)
        for m in range(size):
            t.forward(m*2)
            t.left(360 / sides + 1)
            #第四个螺旋线
        t.penup()
        t.setpos(x,-y)
        t.pendown()
        t.width(thick)
        t.setheading(360 - angle)
        for m in range(size):
            t.forward(m*2)
            t.left(360 / sides + 1)
    turtle.done()        