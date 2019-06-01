# -*- coding: utf-8 -*-
"""
Created on Sun Jun 1 07:45:00 2019

@author: Robin
"""

'''A module to finds all kinds of primes'''
import math
import numpy

def find_primes(num):
    for i in range(2,int(math.sqrt(num)+1)):
        if num % i == 0:
            return False
    return True

def sieve_primes_Eratosthenes(n):
    sieve = numpy.ones(int(n/2), dtype=numpy.bool) 
    limit = int(math.sqrt(n)) + 1 
    
    for i in range(3, limit, 2): 
        if sieve[int(i/2)]:
            sieve[int(i*i/2) :: i] = False
            
    prime_indexes = numpy.nonzero(sieve)[0][1::]
    primes  = 2 * prime_indexes.astype(numpy.int32) + 1 
    return primes