'''
https://rosettacode.org/wiki/Long_primes
A   long prime   (the definition that will be used here)   are primes whose reciprocals   (in decimal)   have a   period length   of one less than the prime number   (also expressed in decimal).
Long primes   are also known as:
  base ten cyclic numbers
  full reptend primes
  golden primes
  long period primes
  maximal period primes
  proper primes
Example
7   is the first long prime,   the reciprocal of seven is   1/7,   which is equal to the repeating decimal fraction   0.142857142857···
The length of the   repeating   part of the decimal fraction is six,   (the underlined part)   which is one less than the (decimal) prime number   7. 
Thus   7   is a long prime.
There are other (more) general definitions of a   long prime   which include wording/verbiage for bases other than ten.
'''

def sieve(limit):
    primes = []
    c = [False] * (limit + 1) # composite = true
    # no need to process even numbers
    p = 3
    while True:
        p2 = p * p
        if p2 > limit: break
        for i in range(p2, limit, 2 * p): c[i] = True
        while True:
            p += 2
            if not c[p]: break
 
    for i in range(3, limit, 2):
        if not c[i]: primes.append(i)
    return primes
 
# finds the period of the reciprocal of n
def findPeriod(n):
    r = 1
    for i in range(1, n): r = (10 * r) % n
    rr = r
    period = 0
    while True:
        r = (10 * r) % n
        period += 1
        if r == rr: break
    return period
 
primes = sieve(64000)
longPrimes = []
for prime in primes:
    if findPeriod(prime) == prime - 1:
        longPrimes.append(prime)
numbers = [500, 1000, 2000, 4000, 8000, 16000, 32000, 64000]
count = 0
index = 0
totals = [0] * len(numbers)
for longPrime in longPrimes:
    if longPrime > numbers[index]:
        totals[index] = count
        index += 1
    count += 1
totals[-1] = count
print('The long primes up to 500 are:')
print(str(longPrimes[:totals[0]]).replace(',', ''))
print('\nThe number of long primes up to:')
for (i, total) in enumerate(totals):
    print('  %5d is %d' % (numbers[i], total))