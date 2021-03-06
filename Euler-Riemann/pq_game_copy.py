
import os
import sys
import math
import logging

DEBUG = False

cur_path = os.path.dirname(os.path.abspath(sys.argv[0]))
logging.basicConfig(level=logging.DEBUG,#控制台打印的日志级别
					#a是追加模式，默认如果不写的话，就是追加模式
					format='%(asctime)s - %(pathname)s:%(lineno)d - %(levelname)s: %(message)s',
					#日志格式
					handlers=[logging.FileHandler(cur_path+'new.log'), logging.StreamHandler()]
					)

logging.debug(u"------------------开始------------------------")
pq_debug_list = []

p = 21179
q = 21187
pq = 448719473
p1 = 9
q1 = 7

ps = [2,1,1,7,9]
qs = [2,1,1,8,7]
pqs = [4,4,8,7,1,9,4,7,3]
L = len(pqs)

def calcQP(c, k):
    res_pq = []
    for px in range(0,10):
        for qx in range(0,10):
            sx = px*q1+p1*qx+k
            if sx%10==c:  #求个位数
                res_pq.append({'p':px,'q':qx,'k':(sx//10)})
                #print(f"{p1}*{qx}+{q1}*{px}+{k} % 10 == {c}       {sx//10}")
                break

    #print("------------------------------")
    return res_pq

pq2 = []
k = p1*q1//10
pq2 = calcQP(pqs[L-2], k)

for x2 in range(0, len(pq2)):
    pq3 = []
    #从十位数上的数字组合中选一组来计算对应的一组百位数上的数字
    k = pq2[x2]['p']*pq2[x2]['q'] + pq2[x2]['k']
    pq3 = calcQP(pqs[L-3], k)

    for x3 in range(0, len(pq3)):
        pq4 = []
        #从百位数上的数字组合中选一组来计算对应的一组千位数上的数字
        k = pq3[x3]['p']*pq2[x2]['q'] + pq2[x2]['p']*pq3[x3]['q'] + pq3[x3]['k']
        pq4 = calcQP(pqs[L-4], k)

        for x4 in range(0, len(pq4)):
            pq5 = []
            #从千位数上的数字组合中选一组来计算对应的一组万位数上的数字
            k = pq4[x4]['p']*pq2[x2]['q'] + pq3[x3]['p']*pq3[x3]['q'] + pq2[x2]['p']*pq4[x4]['q'] + pq4[x4]['k']
            pq5 = calcQP(pqs[L-5], k)

            for x5 in range(0, len(pq5)):

                pnew = int(f"{pq5[x5]['p']}{pq4[x4]['p']}{pq3[x3]['p']}{pq2[x2]['p']}{p1}")
                qnew = int(f"{pq5[x5]['q']}{pq4[x4]['q']}{pq3[x3]['q']}{pq2[x2]['q']}{q1}")
                pqnew = pnew*qnew
                pq_debug_list.append((pnew, qnew, pqnew))
                #print(f"==: {pnew:05d} * {qnew:05d} = {pqnew:010d}")
                
                if DEBUG and pq2[x2]['p'] == 7 and pq2[x2]['q'] == 8 and pq3[x3]['p'] == 1 \
                    and pq3[x3]['q'] == 1 and pq4[x4]['p'] == 1 and pq4[x4]['q'] == 1:
                    pnew = int(f"{pq5[x5]['p']}{pq4[x4]['p']}{pq3[x3]['p']}{pq2[x2]['p']}{p1}")
                    qnew = int(f"{pq5[x5]['q']}{pq4[x4]['q']}{pq3[x3]['q']}{pq2[x2]['q']}{q1}")
                    print(f"==: {pnew:05d} * {qnew:05d} = {pnew*qnew:09d}")

                #验证万位
                k = pq5[x5]['p']*pq2[x2]['q'] + pq4[x4]['p']*pq3[x3]['q'] + pq3[x3]['p']*pq4[x4]['q'] + pq2[x2]['p']*pq5[x5]['q'] + pq5[x5]['k']
                #print(f"{sum%10}")
                if k % 10 != pqs[L-6]:
                    continue

                #验证十万位
                k = k // 10
                k = pq5[x5]['p']*pq3[x3]['q'] + pq4[x4]['p']*pq4[x4]['q'] + pq3[x3]['p']*pq5[x5]['q'] + k
                #print(f"{sum%10}")
                if k % 10 != pqs[L-7]:
                    continue       
                
                #验证百万位
                k = k // 10
                k = pq5[x5]['p']*pq4[x4]['q'] + pq4[x4]['p']*pq5[x5]['q'] + k
                #print(f"{sum%10}")
                if k % 10 != pqs[L-8]:
                    continue                                   
                
                #验证千万位
                k = k // 10
                k = pq5[x5]['p']*pq5[x5]['q'] + k
                #print(f"{sum%10}")
                if k % 10 != pqs[L-9]:
                    continue               
                #最高位检验（亿）  
                #if sum // 10 != pqs[L-9]:
                #    break
                #finally, prime found!
                #print(f"**: {pq5[x5]['p']}{pq4[x4]['p']}{pq3[x3]['p']}{pq2[x2]['p']}{p1} * {pq5[x5]['q']}{pq4[x4]['q']}{pq3[x3]['q']}{pq2[x2]['q']}{q1} = {pq}")

# 获取列表的第二个元素
def takeFirst(elem):
    return elem[0]

# 指定第二个元素排序
pq_debug_list.sort(reverse = False, key = takeFirst)
#print by reverse order
for pnew, qnew, pqnew in pq_debug_list:
    print(f"==: {pnew:05d} * {qnew:05d} = {pqnew:010d}")                