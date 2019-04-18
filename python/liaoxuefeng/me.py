#!/bin/env python
#coding: utf-8
from functools import reduce

DIGIT=['0','1','2','3','4','5','6','7','8','9']
DIGITS = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}

def int2str_daoxu(n):
    s=''
    while True:
        x=divmod(n,10)
        n = x[0]
        s += DIGIT[x[1]]
        if x[0] == 0:
            break
    return s

def char2num(s):
	return DIGITS[s]
		
def fn(x,y):
	return x*10+y
		
def str2int(s):
	return reduce(fn,map(char2num, s))
	
def str2float(s):
	s1, s2 = s.split('.')
	print(s1+s2)
	num = str2int(s1+s2)
	print(num)
	print("len(s2)=", len(s2))
	num = num / pow(10, len(s2))
	print("num=",num)
	return num

# find: 121,12121,...
def int_daoxu(n):
    pass
   
print(int2str(123))
https://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/001431821084171d2e0f22e7cc24305ae03aa0214d0ef29000