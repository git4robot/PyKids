# -*- coding: utf-8 -*-
"""
Created on Sun Jun 1 07:45:00 2019

@author: Robin
"""

'''A module to finds all kinds of primes'''
from math import sqrt
import numpy
from time import time
def is_prime(n):
    for i in range(2,int(sqrt(n)+1)):
        if n % i == 0:
            return False
    return True

def sieve_primes_Eratosthenes(n):
    sieve = numpy.ones(int(n/2), dtype=numpy.bool) 
    limit = int(sqrt(n)) + 1 
    
    for i in range(3, limit, 2): 
        if sieve[int(i/2)]:
            sieve[int(i*i/2) :: i] = False
            
    prime_indexes = numpy.nonzero(sieve)[0][1::]
    primes  = 2 * prime_indexes.astype(numpy.int32) + 1 
    return primes

'''Before this string, the def don't work ----- After this string, the def can work'''
def find_twins(n):
    primes_n = []
    primes_n = sieve_primes_Eratosthenes(n)
    #孪生素数
    twin_primes = {}
    for ix,xp in enumerate(primes_n):
        if ix == len(primes_n) - 1:
            break
        new_xp = xp + 2
        if new_xp == primes_n[ix+1]:
            twin_primes[xp] = primes_n[ix+1]
            
    print("孪生素数:",twin_primes)
    
def find_reverse(n):
    primes_n = []
    primes_n = sieve_primes_Eratosthenes(n)
    #可逆素数
    reverse_primes = {}
    for ix,xp in enumerate(primes_n):
        reverse_num = int(str(xp)[::-1])
        if is_prime(reverse_num):
            reverse_primes[xp] = reverse_num

    print("可逆素数：",reverse_primes)
   
def find_palindromes(n):
    primes_n = []
    primes_n = sieve_primes_Eratosthenes(n)
    #回文素数
    palin_primes = {}
    for ix,xp in enumerate(primes_n):
        palin_num = int(str(xp)[::-1])
        if is_prime(palin_num) and palin_num == xp and xp > 10:
            palin_primes[xp] = palin_num
    
    print("回文素数：")
    for i in palin_primes:
        print(i)
        
def find_square_palindromes(n):
    primes_n = []
    primes_n = sieve_primes_Eratosthenes(n)
    #平方回文素数
    primes = {}
    for ix,xp in enumerate(primes_n):
        squares = xp**2
        palin = str(squares)[::-1]
        if palin == str(squares) and xp > 10:
            primes[xp] = xp
    
    print("平方回文素数：",)
    for i in primes:
        print(i,i**2)

'''def main():
       start_tm = time()
       find_twins(5000)
       find_reverse(5000)
       find_palindromes(7500)
       find_square_palindromes(10000000)
       print("耗时：%f" % (time() - start_tm))
    
if __name__ == '__main__':
    main()'''