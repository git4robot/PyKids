from tkinter import *
from time import sleep
tk = Tk()
tk.title('move triangle')
def move(event):
    if event.keysym == 'Up':
        for x in range(10):   
            cav.move(1, 0, -5)
            tk.update()
            sleep(0.05)
    elif event.keysym == 'Down':
        for x in range(10):   
            cav.move(1, 0, 5)
            tk.update()
            sleep(0.05)
    elif event.keysym == 'Left':
        for x in range(10):   
            cav.move(1, -5, 0)
            tk.update()
            sleep(0.05)
    else:
        for x in range(10):   
            cav.move(1, 5, 0)
            tk.update()
            sleep(0.05)

def tri():
    for x in range(2):
        cav.create_polygon(10, 10, 10, 60, 50, 35, fill = '#ffd800')

btn = Button(tk, text = 'create a triangle that can move', command = tri)
cav = Canvas(tk, width = 400, height = 400)
btn.pack()
cav.pack()
cav.bind_all('<KeyPress-Up>', move)
cav.bind_all('<KeyPress-Down>', move)
cav.bind_all('<KeyPress-Left>', move)
cav.bind_all('<KeyPress-Right>', move)


