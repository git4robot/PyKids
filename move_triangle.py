# -*- coding: utf-8 -*-
"""
Created on Sat May 11 21:41:04 2019

@author: Robin
"""

import tkinter
tk = tkinter.Tk()
canvas = tkinter.Canvas(tk,width = 400,height = 400)
canvas.pack()
canvas.create_polygon(10,10,10,60,50,35)
def move(event):
    if event.keysym == 'Up':
        canvas.move(1,0,-3)
    elif event.keysym == 'Down':
        canvas.move(1,0,3)
    elif event.keysym == 'Left':
        canvas.move(1,-3,0)
    else:
        canvas.move(1,3,0)
canvas.bind_all('<KeyPress-Up>',move)
canvas.bind_all('<KeyPress-Down>',move)
canvas.bind_all('<KeyPress-Left>',move)
canvas.bind_all('<KeyPress-Right>',move)