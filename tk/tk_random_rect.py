from tkinter import *
from random import randrange
tk = Tk()
def random_rec(width, height):
    x1 = randrange(width)
    y1 = randrange(height)
    x2 = randrange(x1 + randrange(width))
    y2 = randrange(y1 + randrange(height))
    cav.create_rectangle(x1, y1, x2, y2)

btn = Button(tk, text = 'create random rectangles', command = random_rec(500, 500))
cav = Canvas(tk, width = 500, height = 500)
btn.pack()
cav.pack()

    
