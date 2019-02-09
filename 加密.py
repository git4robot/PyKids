 # -*- coding: utf-8 -*-
"""
Created on Sat Feb  9 17:32:34 2019

@author: Administrator
"""

import random
'''
random.random()
ch = ord('A')
print(ch)
asc = chr(ch)
print(asc)
测试
'''
message = input('请输入:')
message = message.upper()
output = ""
for letter in message:
     if letter.isupper(): 
         value = ord(letter) + 13
         letter = chr(value)
         if not letter.isupper():
             value -= 26
             letter = chr(value)
     output += letter
print('密码:',output)