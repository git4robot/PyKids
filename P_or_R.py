# -*- coding: utf-8 -*-
"""
Created on Sun Mar 17 12:37:45 2019

@author: Administrator
"""

import turtle
turtle.speed(25)

nnn = int(turtle.numinput('你想看见几条边的花瓣或多边形?',6))
sss = turtle.textinput('你想看到花瓣还是多边形？','输入r看到花瓣，输入p看到多边形。')
for x in range(nnn):
    if sss == 'r':
        turtle.circle(100)
    else:
        turtle.forward(150)
    turtle.left(360 / nnn)
turtle.done()