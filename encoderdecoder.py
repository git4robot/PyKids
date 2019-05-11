# -*- coding: utf-8 -*-
"""
Created on Fri May 3 18:15:00 2019

@author: Robin
"""

import warnings
message = input("Enter a message to encode or decode: ") #得到信息
key = eval(input("Enter a key value from 1-25: ")) #得到密钥值
eod = input("Do you want to encode or decode?(e/d)") #选择加密或解密
message = message.upper() #大写          
output = ""                        
for letter in message:       
    if eod == "e": #加密
        if letter.isupper(): #确认是否大写(不是字母就不是大写)           
            value = ord(letter) + key #加上密钥 
            letter = chr(value) #返回字母        
            if not letter.isupper(): #确认是否大写(不是字母就不是大写)  
                value -= 26            
                letter = chr(value) 
        output += letter #输出      
    elif eod == "d": #解密
        if letter.isupper(): #确认是否大写(不是字母就不是大写)            
            value = ord(letter) + (26 - key) #加上26-密钥   
            letter = chr(value) #返回字母          
            if not letter.isupper(): #确认是否大写(不是字母就不是大写)    
                value -= 26            
                letter = chr(value)  
        output += letter #输出
print("Output message:", output.lower())