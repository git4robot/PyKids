from random import *
from time import *
def test():
    print('4750 times random')
    smallest = 1e10
    largest = -1e10
    t0 = time()
    for i in range(4750):
        x = random()
        smallest = min(x, smallest)
        largest = max(x, largest)
    t1 = time()
    print(round(t1 - t0, 3), 'sec,', end=' ')
    print('min %g, max %g' % (smallest, largest))

test()


