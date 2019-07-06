# -*- coding: utf-8 -*-
"""
Created on Sat Jul  6 16:21:22 2019

@author: Robin
"""

from tkinter import *
tk = Tk()
def semicircle():
    cav.create_arc(250, 10, 250, 260, extent = 180, style = ARC)
cav = Canvas(tk, width = 500, height = 500)
btn = Button(tk, text = 'create cemicircle', command = semicircle)
cav.pack()
btn.pack()