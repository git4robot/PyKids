# -*- coding: utf-8 -*-
"""
Created on Fri May 3 18:15:00 2019

@author: Robin
"""

import warnings
message = input("Enter a message to encode or decode: ") #得到信息
key = eval(input("Enter a key value from 1-26: ")) #得到密钥值
eod = input("Do you want to encode or decode?") #选择加密或解密
message = message.upper() #大写          
output = ""                        
for letter in message:       
    if eod == "e": #加密
        if letter.isupper():            
            value = ord(letter) + key  
            letter = chr(value)         
            if not letter.isupper():  
                value -= 26            
                letter = chr(value)  
        output += letter        
    elif eod == "d": #解密
        if letter.isupper():            
            value = ord(letter) + (26 - key)  
            letter = chr(value)         
            if not letter.isupper():  
                value -= 26            
                letter = chr(value)  
        output += letter
             
print("Output message: ", output.lower())
