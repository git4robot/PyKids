# -*- coding: utf-8 -*-
"""
Created on Wed May  1 11:34:47 2019

@author: Robin
"""

import random #引入random模块
points = 0 #设置空的分数
keep_going = True
while keep_going:
    dice = [0,0,0,0,0]
    for _ in range(5):
        dice[_] = random.randint(1,6) #使用randint产生随机数(用for连续产生5次)
    print('You rolled:',dice)
    dice.sort() #将数字从小到大排列
    if dice[0] == dice[4]:
        print('Yahtzee!!!') #五个一样
        points += 50 #加50分
    elif dice[0] == dice[3] or dice[1] == dice[4]:
        print('Four of a kind!') #四个一样
        points += 25 #加25分
    elif dice[0] == dice[2] or dice[1] == dice[3] or dice[2] == dice[4]:
        print('Three of a kind') #三个一样
        points += 10 #加10分
    keep_going = (input('Hit [Enter] to keep going,any keys to exit:') == '')       
print('Your points was',points,'.' )
print('Thanks for playing!') #退出提示