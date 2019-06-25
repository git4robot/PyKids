from tkinter import *
tk = Tk()
def line():
   cav.create_line(0, 0, 500, 500)
   cav.create_line(0, 500, 500, 0)

btn = Button(tk, text = 'create line', command = line)
cav = Canvas(tk, width = 500, height = 500)
btn.pack()
cav.pack()


