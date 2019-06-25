# -*- coding: utf-8 -*-
"""
Created on Tue Jun 25 18:38:16 2019

@author: Robin
"""
from turtle import *
t = Pen()
t.hideturtle()
def create_line(x1, y1, x2, y2, speed = 8, thick = 1, color = 'black'):
    t.speed(speed)
    t.width(thick)
    t.color(color)
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
    t.speed(speed)
    t.penup()
    t.setpos(x1, y1)
    t.pendown()
    t.write(text, font=("华文楷体", 14, "normal"))
    done()

def create_circle(x1, y1, radius, speed = 8, thick = 1, outline = 'black', fill = 'white'):
    t.speed(speed)
    t.width(thick)
    t.penup()
    t.setpos(x1, y1)
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
    t.goto(x1, y1)
    t.pendown()
    t.circle(1)
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
    done()

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
    create_line(-100, -100, 100, 100)
    create_rectangle(-100, -100, 100, 100)
    create_triangle(0, 0, 100, 100, -200, -250)
    create_text('Hiturtle!')
    create_circle(0, 0, 75)
    create_semicircle(0, 0, 75)
    create_semicircle(0, 0, 75, True)
    create_polygon([0, 0, 100, 100, 0, 100, 100, 0])
    random_polygon()

