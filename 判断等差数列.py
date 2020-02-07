def is_arithmetic_progression(prog):
    _len = len(prog)
    for i in range(0, _len - 2):
        if prog[i + 1] - prog[i] != prog[i + 2] - prog[i + 1]:
            return '不是'
    return '是'
 
prog1 = [1,5,78234]
prog2 = [1,2,3,4]
 
print (is_arithmetic_progression(prog1))
print (is_arithmetic_progression(prog2))
