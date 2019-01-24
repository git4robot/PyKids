# -*- coding: utf-8 -*-
"""
Created on Tue Jan 22 11:39:31 2019

primes.py 
素数有关的趣味问题
寻找素数：效率比较
1,孪生素数
2,可逆素数
3,回文素数
4,平方回文素数
5,梅森尼数
6,金蝉素数
7,等差素数数列

@author: robot
"""


import numpy
import math
import sys
from time import time
from contextlib import contextmanager
#import multiprocessing

def is_prime(num):
    for i in range(2,int(math.sqrt(num)+1)):
        if num % i == 0:
            return False
    return True

def sieve_primes_Eratosthenes(n):

    # Find all primes n > prime > 2 using the Sieve of Eratosthenes 
    # For efficiency, track only odd numbers (evens are nonprime)

    sieve = numpy.ones(int(n/2), dtype=numpy.bool) 
    limit = int(math.sqrt(n)) + 1 
    
    for i in range(3, limit, 2): 
        if sieve[int(i/2)]:
            sieve[int(i*i/2) :: i] = False
            
    prime_indexes = numpy.nonzero(sieve)[0][1::]
    primes  = 2 * prime_indexes.astype(numpy.int32) + 1 
    return primes


def is_even(i): 
    return i % 2 == 0

def is_odd( i): 
    return not is_even(i)

def make_odd(i, delta):
    assert delta in (-1, 1)
    return i if is_odd(i) else i + delta  


'''
def seg_sieve_primes(seg_range):
    # Segmented Sieve of Sieve of Eratosthenes finds primes in a range.

    # As in sieve_primes(), only odd numbers are tracked (evens are nonprime)
    # So first adjust the start/end of the segement so they're odd numbers, then
    # map into the sieve as follows: [seg_start, seg_start+1*2...seg_start+n*2]
    seg_start, seg_end = seg_range
    seg_start = make_odd(seg_start, +1)
    seg_end   = make_odd(seg_end,   -1)
    seg_len   = seg_end - seg_start + 1 
    sieve_len = (seg_len + 1) // 2      # only track odds; evens nonprime
    sieve = numpy.ones(sieve_len, dtype=numpy.bool) 

    # Find a short list of primes used to strike out non-primes in the segment
    root_limit = int(math.sqrt(seg_end)) + 1 
    root_primes = sieve_primes_Eratosthenes(root_limit)
    assert seg_len > root_limit

    for root_prime in root_primes:

        # find the first odd multiple of root_prime within the segment 
        prime_multiple = seg_start - seg_start % root_prime
        while not( is_odd(prime_multiple) and (prime_multiple >= seg_start) ):
            prime_multiple += root_prime

        # strike all multiples of the prime in the range...
        sieve_start = (prime_multiple - seg_start) // 2
        sieve[sieve_start : sieve_len : root_prime] = False

        # ...except for the prime itself
        if seg_start <= root_prime <= seg_end:
            ix = (root_prime - seg_start) // 2
            sieve[ix] = True

    prime_indexes = numpy.nonzero(sieve)[0]  
    primes  = 2 * prime_indexes.astype(numpy.int32) + seg_start 
    return primes


def ints_tostring(ints_arr, line_chars=10):

    # Converts an array of ints to ASCII codes in a bytestring.
    # This is ugly but faster than numpy's .tofile()

    buf  = numpy.zeros(shape=(len(ints_arr), line_chars), dtype=numpy.int8) 
    buf[:, line_chars-1] = 10   # 10 = ASCII linefeed
    for buf_ix in range(line_chars-2, 0-1, -1):
        numpy.mod(ints_arr, 10, out=buf[:, buf_ix])
        buf[:, buf_ix] += 48    # 48 = ASCII '0'
        ints_arr /= 10        
    return buf.tostring()


def seg_prime_string(seg_range):
    primes = seg_sieve_primes(seg_range)
    return ints_tostring(primes)
    # NOTE This returns a string back to the parent process, and to do so 
    # multiprocessing pickles/unpickles it. That's inefficient. 
    # Perhaps use shared memory here? e.g. multiprocessing.Value?

def singleprocess_calc_primes(n, file_name):
    fout = open(file_name, "wb")
    prime_string = ints_tostring(sieve_primes_Eratosthenes(n))
    fout.write(prime_string)
    fout.close()


def multiprocess_calc_primes(n, n_processes, file_name):

    # First, create seperate non-overlapping ranges so multiple 
    # processes can work on sieve segments independently 
    seg_size = n // n_processes
    seg_ranges = [(s, min(n, s+seg_size)) for s in range(2, n, seg_size)]
    if len(seg_ranges) > n_processes:
        # merge the last 2 ranges (if there's a bit left over)
        range1_start, range1_end = seg_ranges.pop()
        range2_start, range2_end = seg_ranges.pop()
        range_merged = (range2_start, range1_end)
        seg_ranges.append(range_merged)
    
    # Launch the processes to work on each sieve segment.
    # Each returns string of primes to write to the .CSV file
    processes = multiprocessing.Pool(n_processes)
    prime_strings = processes.map(seg_prime_string, seg_ranges)
    
    fout = open(file_name, "wb")
    for prime_string in prime_strings:
        fout.write(prime_string)
    fout.close()
'''

@contextmanager
def timer(label):
    # timer(), as suggested by Sang Han 
    output = '{label}: {time:03.3f} sec'
    start = time()
    try:
        yield
    finally:
        end = time()
    print(output.format(label=label, time=end-start))
    sys.stdout.flush()

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
    print(primes_n)
    print(twin_primes)
    
def find_reverse(n):
    primes_n = []
    primes_n = sieve_primes_Eratosthenes(n)
    #可逆素数
    reverse_primes = {}
    for ix,xp in enumerate(primes_n):
        reverse_num = int(str(xp)[::-1])
        if is_prime(reverse_num):
            reverse_primes[xp] = reverse_num
    print(primes_n)
    print(reverse_primes)
    
def main():
    start_tm = time()
    # find_twins(2500)
    find_reverse(25000)
    
    print("耗时：%f" % (time() - start_tm))
    
    # Using 945M as a bound yields a CSV of primes that is 
    # just under the 512MB Kaggle Scripts disk limit
    '''
    mil = 1000000
    upper_bound = (1000 - 55)*mil  
    
    file_multiprocess  = 'primes_multiprocess.csv'
    file_singleprocess = 'primes_singleprocess.csv'

    n_CPUs = multiprocessing.cpu_count()
    n_processes  = n_CPUs

    print("\n>>> PRIME NUMBER CALCULATION <<<")
    print("\nNumber of CPUs detected:", n_CPUs)
    print("Now finding all primes less than :", upper_bound)

    with timer("Multi-process  primes calculation"):
        multiprocess_calc_primes(upper_bound, n_processes, file_multiprocess)

    # with timer("Single-process primes calculation"):
    #    singleprocess_calc_primes(upper_bound, file_singleprocess)
    '''
    print()


if __name__ == '__main__':
    main()