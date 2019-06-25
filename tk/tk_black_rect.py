from tkinter import *
tk = Tk()
tk.title('big black rectangle')
def rec():
    cav.create_rectangle(0, 0, 500, 500, fill = 'black')

btn = Button(tk, text = 'create a big black rectangle', command = rec)
cav = Canvas(tk, width = 500, height = 500)
btn.pack()
cav.pack()
