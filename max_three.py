def max_1(n1, n2, n3):
    if n1 >= n2 and n1 >= n3:
        max = n1
    elif n2 >= n1 and n2 >= n3:
        max = n2
    else:
        max = n3
    print(max)  
    return max

def max_2(n1, n2, n3):
    max = n1
    if n2 or n3 >= n1:
        if n2 >= n3:
            max = n2
        else:
            max = n3
    else:
        max = n1
    print(max)
    return max

def max_3(n1, n2, n3):
    max = n1
    if n2 >= max:
        max = n2
    elif n3 >= max:
        max = n3
    print(max)       
    return max

def max_n():
    n = eval(input('How many numbers?'))
    max = eval(input('Enter a number: '))
    for x in range(n - 1):
        i = eval(input('Enter a number: '))
        if i >= max:
            max = i
    print(max)       
    return max

def max_func(n1, n2, n3):
    print(max(n1, n2, n3))
    return max

def test(n1, n2, n3):
    try:
        max_func(n1, n2, n3)
    except Exception as e:
        print('Error: %s' % e)
    else:
        max_1(n1, n2, n3)
        max_2(n1, n2, n3)
        max_3(n1, n2, n3)
        max_func(n1, n2, n3)
    finally:
        print('Okey, we are done!')

test(41, '125425', 13551)
test(41, 1254252794658, 135512665894)
max_n()
