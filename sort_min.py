# -*- coding: utf-8 -*-
"""
Created on Thu Feb 28 20:03:14 2019

@author: Administrator
"""

a = [3,7,29,21,74,6,93,22,37,67,15]
t = 0
num = len(a)

for i in range(0,num-1):
    for j in range(0,num-1):
        if a[j+1] < a[j]:
            t = a[j]
            a[j] = a[j+1]
            a[j+1] = t

print(a)
