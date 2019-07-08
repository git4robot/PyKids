# -*- coding: utf-8 -*-
"""
Created on Tue Jun 25 18:45:15 2019 China Shanghai
Module Name: turtleTk
@author: Robin 注：需要取消注释调用demo函数。
"""
"""A module to draw tkinter on turtlescreen."""
from turtle import *
t = Pen()
t.hideturtle()
setup(500, 500)


random_functions = ['random_polygon', 'one_random_rectangle']
demo_function = ['demo']
functions = ['create_canvas', 'create_line', 'create_rectangle', 'create_triangle',
             'create_text', 'create_circle', 'create_semicircle', 'create_polygon',
             random_functions, demo_function]


if 'create_semicircle' in functions:
    version = 1.5
if 'create_polygon' in functions:
    version = 2.0
if random_functions and demo_function in functions:
    version = 2.5
if 'one_random_rectangle' in random_functions:
    version = 3.0
else:
    version = 1.0
print('TurtleTk %s (v%s, Jun 30 2019, 08:45:15) ' % (version, version))

"""
Argument:
    x1/y1/x2/y2/points/... ----- The postion of the image.
    width/height ----- The big of the screen.
    speed ----- The turtlepen's speed.
    thick ----- The turtlepen's width(thick).
    outline ----- The turtlepen's color.
    fill ----- The picture's color.
    size ----- The text's size.
    radius ----- The circle or semicircle's radius.
    up ----- The semicircle's degrees left or right(True/False(default)).
    many ----- How many are random polygon.

Example:
    >>> from turtleTk import *
    >>> create_text('HiHello!')
"""
def create_canvas(width = 500, height = 500, color = 'white'):
    setup(width, height)
    bgcolor(color)

def create_line(x1, y1, x2, y2, speed = 8, thick = 1, outline = 'black'):
    t.speed(speed)
    t.width(thick)
    t.color(outline)
    t.penup()
    t.setpos(x1, y1)
    t.pendown()
    t.goto(x2, y2)
    t.penup()
    done()

def create_rectangle(x1, y1, x2, y2, speed = 8, thick = 1, outline = 'black', fill = 'white'):
    t.speed(speed)
    t.width(thick)
    t.penup()
    t.setpos(x1, y1)
    if fill != 'white':
        t.color(fill)
        t.begin_fill()
    t.color(outline)
    t.pendown()
    t.goto(x2, y1)
    t.goto(x2, y2)
    t.goto(x1, y2)
    t.goto(x1, y1)
    if fill != 'white':
        t.color(fill)
        t.end_fill()
    t.penup()
    done()

def create_triangle(x1, y1, x2, y2, x3, y3, speed = 8, thick = 1, outline = 'black', fill = 'white'):
    t.speed(speed)
    a = ((x2 - x1) ** 2 + (y2 - y1) ** 2) ** 0.5
    b = ((x3 - x2) ** 2 + (y3 - y2) ** 2) ** 0.5
    c = ((x3 - x1) ** 2 + (y3 - y1) ** 2) ** 0.5
    if (a + b <= c) or (a + c <= b) or (b + c <= a):
        print('不能组成三角形！')
    t.width(thick)
    t.penup()
    t.setpos(x1, y1)
    if fill != 'white':
        t.color(fill)
        t.begin_fill()
    t.color(outline)
    t.pendown()
    t.goto(x2, y2)
    t.goto(x3, y3)
    t.goto(x1, y1)
    if fill != 'white':
        t.color(fill)
        t.end_fill()
    t.penup()
    done()

def create_text(text, x1 = 0, y1 = 0, size = 35):
    t.penup()
    t.setpos(x1, y1)
    t.pendown()
    t.write(text, font=("华文楷体", 25, "normal"))
    done()

def create_circle(centerx, centery, radius, speed = 8, thick = 1, outline = 'black', fill = 'white'):
    t.speed(speed)
    t.width(thick)
    t.penup()
    t.setpos(centerx, centery)
    t.left(90)
    t.forward(radius)
    t.left(90)
    if fill != 'white':
        t.color(fill)
        t.begin_fill()
    t.color(outline)
    t.pendown()
    t.circle(radius)
    if fill != 'white':
        t.color(fill)
        t.end_fill()
    t.penup()
    t.goto(centerx, centery)
    if fill == 'white':  
        t.pendown()
        t.circle(1)
        t.penup()
    done()

def create_semicircle(x1, y1, radius, up = False, speed = 8, thick = 1, outline = 'black'):
    t.speed(speed)
    t.width(thick)
    t.penup()
    t.setpos(x1, y1)
    t.color(outline)
    t.right(90)
    t.pendown()
    if up == True:
        t.circle(radius, -180)
    else:
        t.circle(radius, 180)
    t.penup()
    done()

def create_polygon(points, speed = 8, thick = 1, outline = 'black', fill = 'white'):
    t.speed(speed)
    t.width(thick)
    t.penup()
    if fill != 'white':
        t.color(fill)
        t.begin_fill()
    t.color(outline)
    t.pendown()
    for x, y in points:
        t.goto(x, y)
    t.goto(points[0])
    if fill != 'white':
        t.color(fill)
        t.end_fill()
    t.penup()
    done()

def one_random_rectangle():
    from random import randrange, choice
    colors = ['green', 'red', 'blue', 'pink', 'purple', 'violet', 'magenta', 'cyan']
    x11 = randrange(-250, 250)
    x22 = randrange(-250, 250)
    y11 = x11 + randrange(-50, 20)
    y22 = x22 + randrange(-50, 20)
    color = choice(colors)
    create_rectangle(x11, y11, x22, y22, fill = color)

def random_polygon(many = 75):
    from random import randint
    a = []
    for q in range(many):
        x = randint(-250, 250)
        y = randint(-250, 250)
        p = (x, y)
        a.append(p)
    create_polygon(a)

def demo():
    #create_line(-100, -100, 100, 100)
    #create_rectangle(-100, -100, 100, 100)
    #create_triangle(0, 0, 100, 100, -200, -250)
    create_text('Hiturtle!')
    #create_circle(0, 0, 75)
    #create_semicircle(0, 0, 75)
    #create_semicircle(0, 0, 75, True)
    #create_polygon([0, 0, 100, 100, 0, 100, 100, 0])
    #one_random_rectangle()
    #random_polygon()
    #one_random_rectangle()
    pass