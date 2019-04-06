# -*- coding: utf-8 -*-
"""
Created on Wed Mar 20 20:55:35 2019

@author: Robot
"""

class Things:
    pass


class Animate(Things):
    pass

class Animals(Animate):
    def breathe(self):
        print('breathing')
    def move(self):
        print('moving')
    def eat_food(self):
        print('eating food')

class Mammals(Animals):
    pass

class Pandas(Mammals):
    pass

class Giraffes(Mammals):
    pass


class Inanimate(Things):
    pass

class Sidewalks(Inanimate):
    pass

class MyMath:
    def Add(self,a,b):
        return a+b
    def Minus(self,a,b):
        return a-b
    def Div(self,a,b):
        if b == 0:
            print("Error, 0")
            return 0
        return a/b
    
    

if __name__ == '__main__':
    myMath = MyMath()
    res = myMath.Add(10,20)
    print(res)
    res = myMath.Minus(20,10)
    print(res)
    res = myMath.Div(10,2)
    print(res)
    
    '''
    ani = Animals()
    ani.breathe()
    ani.eat_food()
    ani.move()
    '''
