# -*- coding: utf-8 -*-
"""
Created on Wed Feb 27 19:17:04 2019

@author: Administrator
"""

import turtle
import random
t = turtle.Pen()
t.speed(750)
turtle.bgcolor('black')
colors = ['red','yellow','blue','green','purple','gray','brown','white']

for n in range(0,25):
    no = random.randint(0,7)
    print(no)
    turtle.pencolor(colors[no])   #random.choice(colors)
    size = random.randint(10,40)
    x = random.randrange(-turtle.window_width()//2,turtle.window_width()//2)
    y = random.randrange(-turtle.window_height()//2,turtle.window_height()//2)
    turtle.penup()
    turtle.setpos(x,y)
    turtle.pendown()
    for m in range(0,size):
        turtle.forward(m * 2)
        turtle.left(91)
turtle.done()