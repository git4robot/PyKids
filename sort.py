'''A module to sort list'''
from time import time

def insertionsort(list):
    '''插入排序：它的工作原理是在已排序序列中从后向前扫描，找到相应位置并插入'''
    t1 = time()
    for x in range(1, len(list)):
        key = list[x]
        j = x - 1
        while j >= 0 and key < list[j]:
            list[j + 1] = list[j]
            j -= 1
        list[j + 1] = key
    t2 = time()
    print('Insertion sorted list:')
    for i in range(len(list)): 
        print("%d" % list[i])
    print('耗时：%f' % (t2 - t1))

def selectionsort(list):
    '''选择排序：在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，然后再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。以此类推，直到所有元素均排序完毕'''
    t1 = time()
    for x in range(len(list)):
        min_idx = x
        for j in range(x + 1, len(list)): 
            if list[min_idx] > list[j]: 
                min_idx = j 
        list[x], list[min_idx] = list[min_idx], list[x] 
    t2 = time()
    print('Selection Sorted list:')
    for i in range(len(list)): 
        print("%d" % list[i])
    print('耗时：%f' % (t2 - t1))

def bubblesort(list):
    '''冒泡排序：重复地走访过要排序的数列，一次比较两个元素，如果他们的顺序错误就把他们交换过来'''
    n = len(list)
    t1 = time()
    for x in range(n):
        for j in range(0, n - x - 1):
            if list[j] > list[j + 1]:
                list[j], list[j + 1] = list[j + 1], list[j]
    t2 = time()
    print('Bubble sorted list:')
    for i in range(len(list)): 
        print("%d" % list[i])
    print('耗时：%f' % (t2 - t1))

def shellsort(list): 
    '''希尔排序：先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，待整个序列中的记录"基本有序"时，再对全体记录进行依次直接插入排序'''
    n = len(list)
    gap = int(n / 2)
    t1 = time()
    while gap > 0: 
        for i in range(gap, n): 
            temp = list[i] 
            j = i 
            while j >= gap and list[j - gap] > temp: 
                list[j] = list[j - gap] 
                j -= gap 
            list[j] = temp 
        gap = int(gap / 2)
    t2 = time()
    print('Shell sorted list:')
    for i in range(len(list)): 
        print("%d" % list[i])
    print('耗时：%f' % (t2 - t1))

a = [3,4,5,6,45,643,6]
insertionsort(a)
selectionsort(a)
bubblesort(a)
shellsort(a)

