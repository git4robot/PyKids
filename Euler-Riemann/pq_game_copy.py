
import math


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
            sx = px*q1+qx*p1+k
            if sx%10==c:  #求个位数
                res_pq.append({'p':px,'q':qx,'k':(sx//10)})
                print(f"{p1}*{qx}+{q1}*{px}+{k} % 10 == {c}       {sx//10}")

    print("------------------------------")
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
                #验证万位
                sum = pq5[x5]['p']*pq2[x2]['q'] + pq4[x4]['p']*pq3[x3]['q'] + pq3[x3]['p']*pq4[x4]['q'] + pq2[x2]['p']*pq5[x5]['q'] + pq5[x5]['k']
                #print(f"{sum%10}")
                if sum % 10 != pqs[L-6]:
                    break
                
                #验证十万位
                k = sum // 10
                sum = pq5[x5]['p']*pq3[x3]['q'] + pq4[x4]['p']*pq4[x4]['q'] + pq3[x3]['p']*pq5[x5]['q'] + k
                #print(f"{sum%10}")
                if sum % 10 != pqs[L-7]:
                    break       
                
                #验证百万位
                k = sum // 10
                sum = pq5[x5]['p']*pq4[x4]['q'] + pq4[x4]['p']*pq5[x5]['q'] + k
                #print(f"{sum%10}")
                if sum % 10 != pqs[L-8]:
                    break                                   
                
                #验证千万位
                k = sum // 10
                sum = pq5[x5]['p']*pq5[x5]['q'] + k
                #print(f"{sum%10}")
                if sum % 10 != pqs[L-9]:
                    break               
                #最高位检验（亿）  
                #if sum // 10 != pqs[L-9]:
                #    break
                #finally, prime found!
                print(f"Bingo: {pq5[x5]['p']}{pq4[x4]['p']}{pq3[x3]['p']}{pq2[x2]['p']}{p} * {pq5[x5]['q']}{pq4[x4]['q']}{pq3[x3]['q']}{pq2[x2]['q']}{q}  = {pq}")