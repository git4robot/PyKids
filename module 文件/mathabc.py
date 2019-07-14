'''A module to calculate numbers.
Version -- 2.5.5(at python 3+)'''

__all__ = ['InputError', 'add', 'minus', 'addadd', 'divide']

class InputError(BaseException):
    pass

def add(n1, n2):
    '''print n1 + n2'''
    try:
        n1 + n2
    except Exception as e:
        print('Invalid input: %s' % e)
    else:
        print('%s + %s = %s' % (n1, n2, n1 + n2))

def minus(n1, n2):
    '''print n1 - n2'''
    try:
        n1 - n2
    except Exception as e:
        print('Invalid input: %s' % e)
    else:
        print('%s - %s = %s' % (n1, n2, n1 - n2))

def addadd(n1, n2):
    '''print n1 * n2'''
    try:
        n1 * n2
    except Exception as e:
        print('Invalid input: %s' % e)
    else:
        print('%s * %s = %s' % (n1, n2, n1 * n2))

def divide(n1, n2):
    '''print n1 / n2'''
    try:
        n1 / n2
    except Exception as e:
        print('Invalid input: %s' % e)
    else:
        if n1 / n2 == round(n1 / n2):
            print('%s / %s = %s' % (n1, n2, n1 // n2))
        else:
            print('%s / %s = %s ...... %s' % (n1, n2, n1 // n2, n1 - (n1 // n2) * n2))
            assert n1 - (n1 // n2) * n2 < n2

def addaddadd(n1, b):
    '''print n1 ** n2'''
    try:
        n1 ** b
    except Exception as e:
        print('Invalid input: %s' % e)
    else:
        print('%s ** %s = %s' % (n1, b, n1 ** b))

def divide_no_last(n1, n2):
    '''print n1 // n2'''
    try:
        n1 // n2
    except Exception as e:
        print('Invalid input: %s' % e)
    else:
        print('%s // %s = %s' % (n1, n2, n1 // n2))

def divide_last(n1, n2):
    '''print n1 % n2'''
    try:
        n1 % n2
    except Exception as e:
        print('Invalid input: %s' % e)
    else:
        print('%s % %s = %s' % (n1, n2, n1 % n2))

if __name__ == "__main__":
    divide(15, 'g')


