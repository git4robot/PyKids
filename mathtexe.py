# -*- coding: utf-8 -*-
"""
Created on Mon Jun 24 16:37:04 2019

@author: Robin
"""
def add(a, b):
    print(a + b)

def subduction(a, b):
    print(a - b)

def addadd(a, b):
    print(a * b)
    
def div(a, b):   
    try:
        a / b
    except ZeroDivisionError:
        print('Division by 0!')
    except TypeError:
        print('You must input a number!')
    except:
        print('Sorry, this cannot work.')
    else:
        c = a // b
        l = a - c * b
        if l >= b:
            raise TypeError
        print('%d...%d' % (c, l))
    finally:
        pass
    
add(375985,345)
subduction(813345,124)
addadd(2532,16)
div(26246,26)