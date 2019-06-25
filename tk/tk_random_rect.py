from tkinter import *
from random import randrange
tk = Tk()
tk.title('random rectangles')
def random_rec():
    for x in range(100):
        x1 = randrange(0, 500)
        y1 = randrange(0, 500)
        x2 = randrange(x1 + randrange(0, 500))
        y2 = randrange(y1 + randrange(0, 500))
        cav.create_rectangle(x1, y1, x2, y2)

btn = Button(tk, text = 'create random rectangles', command = random_rec)
cav = Canvas(tk, width = 500, height = 500)
btn.pack()
cav.pack()

    
