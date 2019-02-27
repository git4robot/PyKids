# -*- coding: utf-8 -*-
"""
Created on Wed Feb 27 18:31:21 2019

@author: Administrator
"""

import turtle
t = turtle.Pen
def up():
    t.forward(50)
def left():
    t.left(90)
def right():
    t.right(90)
def backward():
    t.backward(90)
turtle.onkeypress(up,"Up")
turtle.onkeypress(left,"Left")
turtle.onkeypress(right,"Right")
turtle.onkeypress(backward,"Down")
turtle.listen()