# -*- coding: utf-8 -*-
"""
Created on Thu Jan 31 19:53:56 2019

@author: Administrator
"""

#import math
import random

people = [0] * 8
dhb = 8 * 8.8

tot = 0.0;
for x in range(0,8):
    per = random.random()
    tot += per
    #print(per,tot)
    
while True:
    t_dhb = dhb
    for x in range(0,8):
        hb = random.uniform(0.1,t_dhb)
        hb = round(hb,2)
        people[x] = hb
        #print(x,hb)
        t_dhb = dhb - hb
    
    dhb = max(people)
    print(dhb)
    if dhb < 0.8:
        break