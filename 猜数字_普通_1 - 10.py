# -*- coding: utf-8 -*-
"""
Created on Wed Mar 13 18:23:14 2019

@author: Administrator
"""

import random
n = random.randint(1,10)
while True:
    guess = input('guess a number between 1 and 10:')
    i = int(guess)
    if i == n:
            print('you guessed right')
            break
    if i < n:
            print('try higher')
    if i > n:
            print('try lower')