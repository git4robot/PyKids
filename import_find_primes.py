# -*- coding: utf-8 -*-
"""
Created on Mon Jun 3 17:52:30 2019
需要调用main函数，具体内容请看find_primes.py的第86 - 第95行 注：四位数中没有回文素数
@author: Robin
"""

from time import time
import find_primes as f_p
def main():
       start_tm = time()
       f_p.find_twins(5000)
       f_p.find_reverse(2500)
       f_p.find_palindromes(25000)
       f_p.find_square_palindromes(10000000)
       print("耗时：%f" % (time() - start_tm))
    
if __name__ == '__main__':
    main()
    