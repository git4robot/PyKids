# -*- coding: utf-8 -*-
"""
Created on Fri May 24 20:55:59 2019

@author: Robin
"""

from random import choice
from time import sleep
s = ['clubs','diamonds','hearts','spades']
f = ['three','four','five','six','seven','eight','nine','ten','jack','queen','king','ace','two']
p_s = 0 #玩家的分数
c_s = 0 #电脑的分数
t = 0 #平局次数
for x in range(1,27):
    ms = choice(s)
    mf = choice(f)
    ys = choice(s)
    yf = choice(f)
    print('You have the',mf,'of',ms,'.')
    print('The computer have the',yf,'of',ys,'.')
    if f.index(mf) > f.index(yf):
        print('You win!')
        p_s += 1
    elif f.index(mf) < f.index(yf):
        print('The computer wins!')
        c_s += 1
    else:
        print('It\'s a tie!')
        t += 1
    print()
    sleep(0.075)
if p_s > c_s:
    print('You won this game!')
    print('Your score was:',p_s + t,'.')
elif p_s < c_s:
    print('The computer won this game!')
    print('The computer\'s score was:',c_s + t,'.')
else:
    print('It\'s a tie game!')
print('Thank you to play!')