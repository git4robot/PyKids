from turtle import *
def star1():
      t = Pen()
      t.hideturtle()
      t.speed(0)
      t.width(10)
      t.pencolor('green')
      setup(600, 600)
      t.penup()
      t.goto(10, 200)
      t.pendown()
      for x in range(1, 9):
            t.forward(225)
            t.left(225)

def star2():
      t = Pen()
      t.hideturtle()
      t.speed(0)
      t.width(3)
      t.pencolor('violet')
      setup(600, 600)
      t.penup()
      t.goto(-250, 150)
      t.pendown()
      for x in range(1, 38):
            t.forward(225)
            t.left(175)

def star3():
      t = Pen()
      t.hideturtle()
      t.speed(0)
      t.width(10)
      t.pencolor('blue')
      setup(600, 600)
      t.penup()
      t.goto(-250, -225)
      t.pendown()
      for x in range(1, 20):
            t.forward(225)
            t.left(95)

def star4():
      t = Pen()
      t.hideturtle()
      t.speed(0)
      t.width(5)
      t.pencolor('gold')
      setup(600, 600)
      t.penup()
      t.goto(25, -125)
      t.pendown()
      for x in range(1, 19):
            t.forward(120)
            if x % 2 == 0:
                  t.left(175)
            else:
                  t.left(225)

star1()
star2()
star3()
star4()
exitonclick()
