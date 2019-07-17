
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

pq2 = []
k = p1*q1//10
no = L - 2
for px in range(0,10):
    for qx in range(0,10):
        sx = px*q1+qx*p1+k
        if sx%10==pqs[no]:  #求个位数
            pq2.append({'p':px,'q':qx,'k':(sx//10)})
            print(f"{p1}*{qx}+{q1}*{px}+{k} % 10 == {pqs[no]}       {sx//10}")


print("------------------------------")
pq3 = []
#从十位数上的数字组合中选一组来计算对应的一组百位数上的数字
k = pq2[0]['p']*pq2[0]['q'] + pq2[0]['k']
no = L - 3
for px in range(0,10):
    for qx in range(0,10):
        sx = px*q1+qx*p1+k
        if sx%10==pqs[no]:
            pq3.append({'p':px,'q':qx,'k':(sx//10)})
            print(f"{p1}*{qx}+{q1}*{px}+{k} % 10 == {pqs[no]}       {sx//10}")


print("------------------------------")
pq4 = []
#从百位数上的数字组合中选一组来计算对应的一组千位数上的数字
k = pq3[0]['p']*pq2[0]['q'] + pq2[0]['p']*pq3[0]['q'] + pq3[0]['k']
no = L - 4
for px in range(0,10):
    for qx in range(0,10):
        sx = px*q1+qx*p1+k
        if sx%10==pqs[no]:
            pq4.append({'p':px,'q':qx,'k':(sx//10)})
            print(f"{p1}*{qx}+{q1}*{px}+{k} % 10 == {pqs[no]}       {sx//10}")   

print("------------------------------")
pq5 = []
#从千位数上的数字组合中选一组来计算对应的一组万位数上的数字
k = pq4[0]['p']*pq2[0]['q'] + pq3[0]['p']*pq3[0]['q'] + pq2[0]['p']*pq4[0]['q'] + pq4[0]['k']
no = L - 5
for px in range(0,10):
    for qx in range(0,10):
        sx = px*q1+qx*p1+k
        if sx%10==pqs[no]:
            pq5.append({'p':px,'q':qx,'k':(sx//10)})
            print(f"{p1}*{qx}+{q1}*{px}+{k} % 10 == {pqs[no]}       {sx//10}")

print("------------------------------")            

#验证
sum = pq5[0]['p']*pq2[0]['q'] + pq4[0]['p']*pq3[0]['q'] + pq2[0]['p']*pq4[0]['q'] + pq5[0]['k']
print(f"{sum%10}")