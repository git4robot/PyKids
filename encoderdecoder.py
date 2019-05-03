# -*- coding: utf-8 -*-
"""
Created on Fri May 3 18:15:00 2019

@author: Robin
"""

message = input("Enter a message to encode or decode: ") 
key = eval(input("Enter a key value from 1-26: "))
eod = input("Do you want to encode or decode?")
message = message.upper()           
output = ""                        
for letter in message:       
    if eod == "e":
        if letter.isupper():            
            value = ord(letter) + key  
            letter = chr(value)         
            if not letter.isupper():  
                value -= 26            
                letter = chr(value)  
        output += letter        
    elif eod == "d":
        if letter.isupper():            
            value = ord(letter) + (26 - key)  
            letter = chr(value)         
            if not letter.isupper():  
                value -= 26            
                letter = chr(value)  
        output += letter             
print("Output message: ", output) 