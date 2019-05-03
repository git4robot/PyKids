# -*- coding: utf-8 -*-
"""
Created on Wed May 1 12:25:00 2019

@author: Robin
"""

import random #引入random模块
choices = ['rock','paper','scissors']
player = input('Do you want to be rock, paper, or scissors(or quit)?') #选择
p_scores = 0.0 #保留一位小数
com_scores = 0.0 #保留一位小数
while player != 'quit': #是否退出
    player = player.lower() #变成小写
    com = random.choice(choices) #随机选取(计算机)
    print('You chose '+player+', and the computer chose '+com+'.') #展示选择
    if player == com:
        print('It\'s a tie!') #平局
        p_scores += 0.5 
        com_scores += 0.5
        #玩家和电脑各加0.5分
    elif player == 'rock':
        if com == 'scissors':
            print('Player win!') #石头砸剪刀
            p_scores += 1
        else:
            print('Computer wins!') #布包石头
            com_scores += 1
    elif player == 'paper':
        if com == 'rock':
            print('Player win!') #布包石头
            p_scores += 1
        else:
            print('Computer wins!') #剪刀剪布
            com_scores += 1
    elif player == 'scissors':
        if com == 'paper':
            print('Player win!') #剪刀剪布
            p_scores += 1
        else:
            print('Computer wins!') #石头砸剪刀
            com_scores += 1
    else:
        print('I think there was some sort error...') #玩家输入了无法计算的信息
    print() #打印一行空格
    player = input('Do you want to be rock,paper,or scissors(or quit)?') #再次选择
print('Your score was:',p_scores,', and computer\'s score was:',com_scores,'.') #显示分数
print('Thanks for playing!') #退出提示