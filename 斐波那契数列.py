# -*- coding: utf-8 -*-
"""
Created on Sat Jun  8 19:12:23 2019

@author: Robin
"""
last = 0.0
res = []
def f(n):
    # 第一和第二项
    n1 = 1
    n2 = 1
    count = 2
    if n <= 2:
        print("Must > 2")
        return
    last = n2 * 1.0
    print("斐波那契数列：")
    print("%d, %d, " % (n1, n2), end = '')
    while count < n:
       nth = n1 + n2
       res.append(last / (nth * 1.0))
       print(nth,end=", ")
       # 更新值
       n1 = n2
       n2 = nth
       last = nth
       count += 1
       
if __name__ == '__main__':
    f(30)
    for ro in res:
        print("%.3f," % ro, end = '')