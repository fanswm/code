#!/usr/bin/python
# coding: utf-8
# Filename: math_game.py

#from ctypes import *

#i = c_int(5)
#i.value = 10

#randdll = CDLL('pythonrand.dll')

import random

maxi = 0
while(maxi < 100):
	s = raw_input('请输入和的最大限制值（阿拉伯数字,必须大于100）：')
	maxi = int(s)
	
s = raw_input('今天，你想做几道题呢？请输入阿拉伯数字:')
daoshu = int(s)
s = raw_input('几位数的加法？请输入位数（阿拉伯数字）：')
wei = int(s)

count = 0
while True:
	w = wei
	if  count == daoshu:
		break

	sumi = 0
	a = random.randint(100, maxi)
	print a,
	sumi += a
	#b = random.randint(0, maxi - a)
	w -= 1

	while(w > 0):
		a = random.randint(0, maxi - sumi)
		print '+', a,
		sumi += a
		w -= 1
	print '=',

	s = raw_input()
	result = int(s)
	if result == sumi:
		print '真棒！'
	else:
		print 'NO NO NO! 答案是:', sumi

	count += 1
