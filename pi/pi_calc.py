#https://rosettacode.org/wiki/Pi#Python

def calcPi():
    q, r, t, k, n, l = 1, 0, 1, 1, 3, 3
    while True:
        if 4*q+r-t < n*t:
            yield n	#yield有return功能，
            nr = 10*(r-n*t)
            n  = ((10*(3*q+r))//t)-10*n
            q  *= 10
            r  = nr
        else:
            nr = (2*q+r)*l
            nn = (q*(7*k)+2+(r*l))//(t*l)
            q  *= k
            t  *= l
            l  += 2
            k += 1
            n  = nn
            r  = nr

import sys
#把函数赋值给一个变量（称之为生成器），在后面函数会被执行
pi_digits = calcPi()
i = 0
for d in pi_digits:
	#在标准输出（屏幕）上打印出来
    sys.stdout.write(str(d))
    i += 1
	#位数计数，40个输出后再换一行打印
    if i == 40: print(""); i = 0