#-*- coding: utf-8 -*-
from functools import reduce

DIGITS = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}

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
	
print('str2float(\'123.456\') =', str2float('123.456'))
if abs(str2float('123.456') - 123.456) < 0.00001:
	print('ok!')
else:
	print('error!')
