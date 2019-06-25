from tkinter import *
tk = Tk()
tk.title('arc')
def arc():
    cav.create_arc(10, 10, 200, 80, extent = 45, style = ARC)
    cav.create_arc(10, 80, 200, 160, extent = 90, style = ARC)
    cav.create_arc(10, 160, 200, 240, extent = 135, style = ARC)
    cav.create_arc(10, 240, 200, 360, extent = 180, style = ARC)
    cav.create_arc(10, 320, 200, 400, extent = 359, style = ARC)

btn = Button(tk, text = 'create five diffrent arcs', command = arc)
cav = Canvas(tk, width = 400, height = 400)
btn.pack()
cav.pack()
