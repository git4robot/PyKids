# -*- coding: utf-8 -*-
"""
Created on Mon Jan 21 10:47:04 2019

@author: robot
https://www.bilibili.com/video/av38682310/
"""

import turtle
import time

def click_say(x,y):
    turtle.goto(x,y)
    print("Hi,Yes! (%d, %d)" % (x,y))
    
turtle.setup(500,500)

turtle.shape("turtle") #亀にしている
turtle.pensize(5)
turtle.pencolor("yellow")
turtle.fillcolor("red")
 
turtle.begin_fill()
turtle.forward(100)
turtle.right(90)
turtle.forward(100)
turtle.right(90)
turtle.forward(100)
turtle.right(90)
turtle.forward(100)

time.sleep(0.5)
turtle.penup()
turtle.goto(-150,-120)
turtle.color("violet")
turtle.write("Done", font=('Arial', 40, 'normal'))
time.sleep(1)

turtle.reset()  #清空窗口，重置turtle状态为起始状态
turtle.pensize(3)
turtle.pencolor("red")
turtle.circle(45)
time.sleep(1)
turtle.fillcolor("green")

turtle.clear()
turtle.circle(120,180) # 半圆
time.sleep(1)
turtle.clear()
turtle.penup()
turtle.goto(50,100)
turtle.pendown()
turtle.circle(150,steps=5) # 三角形;
time.sleep(1)

w = turtle.Screen()
w.onclick(click_say)

#进入事件循环
#turtle.mainloop()

turtle.clear()
turtle.reset()

turtle.done()
