# -*- coding: utf-8 -*-
"""
Created on Thu Jun 20 16:30:35 2019
@author: Robin
"""
def write_file(air, outt):
    f = open(outt, 'w')
    f.write(air)
    f.close()

def read_file(inn):
    f = open(inn)
    s = f.read()
    print(s)

def copy_file(inn, outt):
    f = open(inn)
    s = f.read()
    f.close()
    f = open(outt, 'w')
    f.write(s)
    f.close()

copy_file('d:\\text.txt', 'f:\\text_copy.txt')
write_file('hihellopython, pygame, turtle, tkinter, graphics!', 'f:\\py.txt')
read_file('f:\\pyread.txt')