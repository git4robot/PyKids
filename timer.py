from time import *
def timer(second = 60):
    '''A timer for variable second.'''
    s = second
    while True:
        print(s)
        sleep(1)
        s -= 1
        if s == 0:
            print(0)
            break
    return second

def _test():
    '''A test for timer function.'''
    timer(15)
    timer()


