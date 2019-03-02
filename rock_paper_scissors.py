# -*- coding: utf-8 -*-
"""
Created on Sat Mar  2 11:14:11 2019

@author: Administrator
"""
import random

choice = ['rock','paper','scissors']
p_choice = input('What do you want to be?rock or paper or scissors?(or quit?)')
com_choice = random.choice(choice)

while p_choice != quit:
    if p_choice == com_choice:
            print('You chose ' + p_choice + ',and the computer chose '+ com_choice + '.')
            print('It\'s a tie!')
            
    elif p_choice == 'rock':
        print('You chose ' + p_choice + ',and the computer chose '+ com_choice + '.')
        if com_choice == 'scissors':
            print('player win!')
        else:
            print('computer win!')
        
    elif p_choice == 'paper':
        print('You chose ' + p_choice + ',and the computer chose '+ com_choice + '.')
        if com_choice == 'rock':
            print('player win!')
        else:
            print('computer win!')
        
    elif p_choice == 'scissors':
        print('You chose ' + p_choice + ',and the computer chose '+ com_choice + '.')
        if com_choice == 'paper':
            print('player win!')
        else:
            print('computer win!')
                
    elif p_choice == 'quit':
        print('Good bye!')
        break
    
    else:
        print('There was some sort of error...')
        
    p_choice = input('What do you want to be?rock or paper or scissors?(or quit?)')
    com_choice = random.choice(choice)
