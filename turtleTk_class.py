"""A module to draw tkinter on turtlescreen."""
from turtle import *
from sys import *
from sys import _getframe
from os import *
t = Pen()
t.hideturtle()
setup(500, 500)


random_functions = ['random_polygon', 'random_rectangles', 'one_random_rectangle']
demo_function = ['demo']
functions = ['create_canvas', 'create_line', 'create_rectangle', 'create_triangle',
             'create_text', 'create_circle', 'create_semicircle', 'create_polygon',
             random_functions, demo_function]


if 'create_semicircle' in functions:
      tt_version = 1.0
if 'create_polygon' in functions:
      tt_version = 1.5
if random_functions and demo_function in functions:
      tt_version = 2.0
if 'one_random_rectangle' in random_functions:
      tt_version = 2.5
if 'random_rectangles' in random_functions:
      tt_version = 3.0
else:
      tt_version = 0.5
      
def isWindows64():
      return 'PROGRAMFILES(X86)' in environ

try:
      if isWindows64():
            print('TurtleTk %s (Run on python %s:20a20b02a02, Feb 02 2020, 20:20:20) [MSC v%s 64 bit (AMD64)] on win64) ' % (tt_version, version[0:5], tt_version))
      else:
            print('TurtleTk %s (Run on python %s:20a20b02a02, Feb 02 2020, 20:20:20) [MSC v%s 32 bit (Intel)] on win32) ' % (tt_version, version[0:5], tt_version))
except:
      print('TurtleTk %s (Run on python %s:20a20b02a02, Feb 02 2020, 20:20:20) [MSC v%s 64 bit (AMD64)] on win64) ' % (tt_version, version[0:5], tt_version))

  
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
    >>> from turtleTk_class import *
    >>> c = Create()
    >>> c.create_text('HiHello!')
"""

class Create():
      def create_canvas(self, width = 500, height = 500, color = 'white'):
            setup(width, height)
            bgcolor(color)

      def create_line(self, x1, y1, x2, y2, speed = 8, thick = 1, outline = 'black'):
            t.speed(speed)
            t.width(thick)
            t.color(outline)
            t.penup()
            t.setpos(x1, y1)
            t.pendown()
            t.goto(x2, y2)
            t.penup()
            done()

      def create_rectangle(self, x1, y1, x2, y2, speed = 8, thick = 1, outline = 'black', fill = 'white'):
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
            if _getframe(1).f_code.co_name == '<module>' or _getframe(1).f_code.co_name == 'demo':
                  done()

      def create_triangle(self, x1, y1, x2, y2, x3, y3, speed = 8, thick = 1, outline = 'black', fill = 'white'):
            t.speed(speed)
            a = ((x2 - x1) ** 2 + (y2 - y1) ** 2) ** 0.5
            b = ((x3 - x2) ** 2 + (y3 - y2) ** 2) ** 0.5
            c = ((x3 - x1) ** 2 + (y3 - y1) ** 2) ** 0.5
            if (a + b <= c) or (a + c <= b) or (b + c <= a):
                raise ValueError('Could not make triangles!')
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

      def create_text(self, text, x1 = 0, y1 = 0, size = 35):
            t.penup()
            t.setpos(x1, y1)
            t.pendown()
            t.write(text, font=("华文楷体", 25, "normal"))
            done()

      def create_circle(self, centerx, centery, radius, speed = 8, thick = 1, outline = 'black', fill = 'white'):
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
                t.circle(0.5)
                t.penup()
            done()

      def create_semicircle(self, x1, y1, radius, up = False, speed = 8, thick = 1, outline = 'black'):
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

      def create_polygon(self, points, speed = 8, thick = 1, outline = 'black', fill = 'white'):
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


class Random():
      def random_rectangles(self, many = 25):
            for x in range(0, many):
                  self.one_random_rectangle()
      
      def one_random_rectangle(self):
            from random import randrange, choice
            colors = ['green', 'red', 'blue', 'pink', 'purple', 'violet', 'magenta', 'cyan']
            x11 = randrange(-250, 250)
            x22 = randrange(-250, 250)
            y11 = x11 + randrange(-50, 20)
            y22 = x22 + randrange(-50, 20)
            color = choice(colors)
            c = Create()
            c.create_rectangle(x11, y11, x22, y22, fill = color)

      def random_polygon(self, many = 25):
            from random import randint
            a = []
            for q in range(many):
                x = randint(-250, 250)
                y = randint(-250, 250)
                p = (x, y)
                a.append(p)
            c = Create()
            c.create_polygon(a)

def demo():
      c = Create()
      r = Random()
      #c.create_canvas(color = 'blue')
      #c.create_line(-100, -100, 100, 100)
      #c.create_rectangle(-100, -100, 100, 100)
      #c.create_triangle(0, 0, 100, 200, 200, 220)
      #c.create_triangle(0, 0, 0, 0, 200, 220) #Error
      #c.create_text('Hiturtle!')
      #c.create_circle(0, 0, 125, thick = 50) #Very THICC
      #c.create_circle(0, 0, 75, fill = 'green')
      #c.create_semicircle(0, 0, 75)
      #c.create_semicircle(0, 0, 75, True)
      #c.create_polygon([[0, 0], [0, 100], [100, 100], [100, 0]])
      #r.random_rectangles()
      #r.one_random_rectangle()
      #r.random_polygon()

if __name__ == '__main__':
      demo()
