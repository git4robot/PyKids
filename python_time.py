# -*- coding: utf-8 -*-
"""
Created on Sat Mar  2 11:50:38 2019

@author: Administrator
"""
import time

wday = ['一','二','三','四','五','六','日']
t = time.localtime()
in_t = input("请输入日期(如2020 05 09 10:22)：")
t = time.strptime(in_t, "%Y %m %d %H:%M")
#print(t)
year = t[0]
month = t[1]
day = t[2]
hour = t[3]
minute = t[4]
second = t[5]
year_day = t[7]
week_day = t[6]
print('%d 年 %d 月 %d 日 %d 点 %d 分' % (year, month, day, hour, minute))
print()
print(year,'年中的第',year_day,'天,星期%s' % wday[week_day])
