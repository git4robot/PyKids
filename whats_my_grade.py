# -*- coding: utf-8 -*-
"""
Created on Sun Mar 17 12:28:47 2019

@author: Administrator
"""

grade = eval(input('Enter your grade in 0 and 100:'))

if grade == 100:
    print('You got an A+!')
elif grade >= 90 and grade < 100:
    print('You got an A!')
elif grade >= 80 and grade < 100:
    print('You got a B!')
elif grade >= 60 and grade < 100:
    print('You got a C')
else:
    print('You got a D')