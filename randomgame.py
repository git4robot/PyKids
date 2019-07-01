# -*- coding: utf-8 -*-
"""
Created on Thu Jun 27 08:03:33 2019

@author: Robin
"""

from random import randint
from turtle import numinput, done
def tt_game():
    num = randint(1, 100)
    inputn = numinput('Guess a number', 'Guess a number that between 1 and 100:')
    k = True
    while k:
        if num == inputn:
            o = '''%s was the number! You win! Please press [cancel] or input '0' to exit.''' % round(num)
            numinput('Guess right', o)
            done()
            break
        elif num < inputn:
            inputn = numinput('Guess again', 'Guess lower!')
        elif num > inputn:
            inputn = numinput('Guess again', 'Guess higher!') 

