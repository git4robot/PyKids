from tkinter import *
tk = Tk()
tk.title('create a semicircle')
def up():
    cav.create_arc(10, 100, 490, 490, extent = 180, style = ARC)

def down():
    cav.create_arc(10, 100, 490, 490, extent = -180, style = ARC)

def egg():
    up()
    down()

def clear():
    cav.create_rectangle(0, 0, 500, 500, fill = 'white', outline = 'white')

cav = Canvas(tk, width = 500, height = 500)
btn1 = Button(tk, text = 'create cemicircle(up)', command = up).pack()
btn2 = Button(tk, text = 'create cemicircle(down)', command = down).pack()
btn3 = Button(tk, text = 'create an big egg', command = egg).pack()
btn4 = Button(tk, text = 'clear', command = clear).pack()
cav.pack()
tk.mainloop()


