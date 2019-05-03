# -*- coding: utf-8 -*-
"""
Created on Wed May  1 11:34:47 2019

@author: Robin
"""

import random #引入random模块
keep_going = True
while keep_going:
    dice = [0,0,0,0,0]
    for _ in range(5):
        dice[_] = random.randint(1,6) #使用randint产生随机数(用for连续产生5次)
    print('You rolled:',dice) #打印五个数，让玩家知道
    break
