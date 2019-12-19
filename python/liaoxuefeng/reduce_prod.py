# -*- coding: utf-8 -*-
from functools import reduce
def func(x,y):
    return x*y
def prod(L):
    return reduce(func,L)

print('3*5*7*9 = ', prod([3,5,7,9]))
if prod([3,5,7,9]) == 945:
    print('test success!')
else:
    print('test faild!')
