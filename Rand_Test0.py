# -*- coding: utf-8 -*-
"""
Created on Mon May  6 21:35:28 2019

@author: Robin
"""

import random #引入random模块
import numpy as np
import matplotlib.pyplot as plt

rand_info = [0,0,0,0,0,0,0,0,0]

def drawResult():
    # make an array of random numbers with a gaussian distribution with
    # mean = 5.0
    # rms = 3.0
    # number of points = 1000
    #data = np.random.normal(5.0, 3.0, 1000)
    # make a histogram of the data array
    plt.bar(range(len(rand_info)), rand_info)
    # make plot labels
    plt.xlabel('1-6')
    plt.ylabel('count')
    plt.show()


for n in range(0, 100*len(rand_info)):
    index = random.randint(1,9) - 1
    rand_info[index] = rand_info[index]+1
print(rand_info)
drawResult()