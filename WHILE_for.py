# -*- coding: utf-8 -*-
"""
Created on Sun Mar 17 13:02:49 2019

@author: Administrator
"""

import random
step = 0
tired = random.randint(250,750)
bad_weather = random.randint(25,975)
while step <= 1000:
    print(step)
    if tired == True:
        print('Tired!')
        break
    elif bad_weather == True:
        print('Badweather!')
        break
    else:
        step = step + 1