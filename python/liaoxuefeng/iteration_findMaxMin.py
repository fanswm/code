#codeing: utf-8
def findMinMax(L):
    if len(L) == 0:
        return (None, None)
    else:
        max = L[0] 
        min = L[0]
        for i in L:
            if max < i:
                max = i 
            if min > i:
                min = i 
        print('max=%s, min=%s' %(max, min))
        return (min, max)

# 测试
if findMinMax([]) != (None, None):
    print('测试失败!')
elif findMinMax([7]) != (7, 7):
    print('测试失败!')
elif findMinMax([7, 1]) != (1, 7):
    print('测试失败!')
elif findMinMax([7, 1, 3, 9, 5]) != (1, 9):
    print('测试失败!')
else:
    print('测试成功!')
