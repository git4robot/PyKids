# -*- coding: utf-8 -*-
"""
Created on Mon Mar 11 21:59:56 2019

@author: Robot
"""

import random
number = input("Please input:")
guess_number = [0,0,0,0]
for i in range(0,4):
    guess_number[i] = random.randint(1,number + 10)
print(guess_number)
    
if max(guess_number) > number:
    print("You win!")
else:
    print("Boom!You lose.")