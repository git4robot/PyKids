'''A module to calculate numbers.
It takes function add、function minus、function multiplication、function divide、function pow、function floordiv and function delivery.'''

class InputError(BaseException):
    '''Invalid input.''' 
    pass

def add(n1, n2):
    '''print n1 + n2.'''
    try:
        n1 + n2
    except Exception:
        raise InputError from None
    else:
        print('%s + %s = %s' % (n1, n2, n1 + n2))

def minus(n1, n2):
    '''print n1 - n2.'''
    try:
        n1 - n2
    except Exception:
        raise InputError from None
    else:
        print('%s - %s = %s' % (n1, n2, n1 - n2))

def multiplication(n1, n2):
    '''print n1 * n2.'''
    try:
        n1 * n2
    except Exception:
        raise InputError from None
    else:
        print('%s * %s = %s' % (n1, n2, n1 * n2))

def divide(n1, n2):
    '''print n1 / n2.'''
    try:
        n1 / n2
    except Exception:
        raise InputError from None
    else:
        if n1 / n2 == round(n1 / n2):
            print('%s / %s = %s' % (n1, n2, round(n1 / n2)))
        else:
            print('%s / %s = %s ...... %s' % (n1, n2, round(n1 / n2), n1 - (round(n1 / n2) * n2)))

def pow(n1, b):
    '''print n1 ** n2.'''
    try:
        n1 ** b
    except Exception:
        raise InputError from None
    else:
        print('%s ** %s = %s' % (n1, b, n1 ** b))

def floordiv(n1, n2):
    '''print n1 // n2.'''
    try:
        n1 // n2
    except Exception:
        raise InputError from None
    else:
        print('%s // %s = %s' % (n1, n2, n1 // n2))

def delivery(n1, n2):
    '''print n1 % n2.'''
    try:
        n1 % n2
    except Exception:
        raise InputError from None
    else:
        print('%s % %s = %s' % (n1, n2, n1 % n2))


'''Test for mathabc.'''
def _test():
    divide(15, 6)
    divide(15, 'h')

if __name__ == "__main__":
    _test()



