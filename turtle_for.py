# -*- coding: utf-8 -*-
"""
Created on Sat Feb  9 18:14:14 2019

@author: Administrator
"""
import turtle
import time

turtle.setup(width=0.5,height=0.7)
turtle.screensize(50,50,"purple")
turtle.pensize(5)
turtle.speed(1)
turtle.pencolor("yellow")
turtle.fillcolor("blue")
turtle.shape("turtle")

turtle.begin_fill()

for _ in range(7):
    turtle.forward(250)
    turtle.right(102.86)
turtle.end_fill()
time.sleep(2)

turtle.penup()
turtle.goto(-150,-120)
turtle.color("grey")
turtle.write("Done", font=('Arial', 40, 'normal'))
time.sleep(1)

turtle.done()
