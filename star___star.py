# -*- coding: utf-8 -*-
"""
Created on Sun Mar 17 13:08:29 2019

@author: Administrator
"""

import turtle
def mystar(size,filled):
    if filled == True:
        turtle.begin_fill()
    for x in range(1,19):
        turtle.forward(100)
        if x % 2 == 0:
            turtle.left(175)
        else:
            turtle.left(225)
    if filled == True:
        turtle.end_fill()

    

turtle.color(0.9,0.75,0)
mystar(120,True)
turtle.done()