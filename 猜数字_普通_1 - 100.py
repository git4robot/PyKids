# -*- coding: utf-8 -*-
"""
Created on Thu Mar 14 18:36:30 2019

@author: Administrator
"""

import random
n = random.randint(1,100)
while True:
    guess = input('guess a number between 1 and 100:')
    i = int(guess)
    if i == n:
            print('you guessed right')
            break
    if i < n:
            print('try higher')
    if i > n:
            print('try lower')