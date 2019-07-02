# -*- coding: utf-8 -*-
"""
Created on Tue Jul  2 14:36:33 2019

@author: Robin
"""

class Giraffes:
    def left_f(self):
        print('Left foot forward')
    def right_f(self):
        print('Right foot forward')
    
    def left_b(self):
        print('Left foot back')
    def right_b(self):
        print('Right foot back')
    
    def dance(self):
        self.left_f()
        self.left_b()
        self.right_f()
        self.right_b()
        self.left_b()
        self.right_b()
        self.right_f()
        self.left_f()

reginald = Giraffes()
reginald.dance()