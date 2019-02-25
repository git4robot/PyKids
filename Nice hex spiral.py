# -*- coding: utf-8 -*-
"""
Created on Mon Feb 25 20:56:07 2019

@author: Administrator
"""

import turtle
colors = ['blue','purple','green','yellow','orange','brown']

t = turtle.Pen()
turtle.bgcolor('black')
t.speed(50)
for x in range(360):
    t.pencolor(colors[x % 6])
    t.width(x / 100 + 1)
    t.forward(x)
    t.left(59)
turtle.done()