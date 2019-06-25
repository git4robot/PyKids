from turtle import *
t = Pen()
t.hideturtle()
def create_line(x1, y1, x2, y2, speed = 8, thick = 1, color = 'black'):
    t.width(thick)
    t.color(color)
    t.penup()
    t.setpos(x1, y1)
    t.pendown()
    t.goto(x2, y2)
    t.penup()

def create_rectangle(x1, y1, x2, y2, speed = 8, thick = 1, outline = 'black', fill = 'white'):
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

def create_triangle(x1, y1, x2, y2, x3, y3, speed = 8, thick = 1, outline = 'black', fill = 'white'):
    a = ((x2 - x1) ** 2 + (y2 - y1) ** 2) ** 0.5
    b = ((x3 - x2) ** 2 + (y3 - y2) ** 2) ** 0.5
    c = ((x3 - x1) ** 2 + (y3 - y1) ** 2) ** 0.5
    if (a + b <= c) or (a + c <= b) or (b + c <= a):
        print('不能组成三角形！')
        return
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

def create_text(text, x1 = 0, y1 = 0, size = 35):
    t.penup()
    t.setpos(x1, y1)
    t.pendown()
    t.write(text, font=("华文楷体", 14, "normal"))

def create_circle(x1, y1, radius, speed = 8, thick = 1, outline = 'black', fill = 'white'):
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
