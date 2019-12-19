#!/bin/python
# coding: utf-8
def findMinAndMax(L):
    a = L[0]
    min = a
    b = L[0]
    max = b

    if not isinstance(a, b,  (int, float)):
        return (None, None)

    for a, b in L:
        if a < min:
            a = min
        if b > max:
            b = max
    return (min, max)


# 测试
if findMinAndMax([]) != (None, None):
    print('测试失败!')
elif findMinAndMax([7]) != (7, 7):
    print('测试失败!')
elif findMinAndMax([7, 1]) != (1, 7):
    print('测试失败!')
elif findMinAndMax([7, 1, 3, 9, 5]) != (1, 9):
    print('测试失败!')
else:
    print('测试成功!')
