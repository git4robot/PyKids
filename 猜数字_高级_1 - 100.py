# -*- coding: utf-8 -*-
"""
Created on Wed Mar 13 18:15:34 2019

@author: Administrator
"""

import random
n = random.randint(1,100) 
guess = int(input('Guess a number between 1 and 100:'))
while guess != n:
    if guess > n:
        print(guess,'was too high.try again.')
    if guess < n:
        print(guess,'was too low.try again.')
    guess = int(input('Guess again:'))
print(guess,'was the number!you win!')