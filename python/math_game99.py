#!/usr/bin/python
#-*-coding: utf-8 -*-
# Filename: math_game.py

#from ctypes import *

#i = c_int(5)
#i.value = 10

#randdll = CDLL('pythonrand.dll')

import random

s = raw_input("Pleasy input a number: ")
daoshu = int(s)

count = 0
while True:
	a = random.randint(1, 9)
	b = random.randint(1, 9)
	sum = a * b

	print a,'*',b,'=',
	s = raw_input()
	c = int(s)

	if c == sum:
		print "\tPerfect!!!"
	else:
		print "\tNo no no!!! The answer is: ", sum

	count += 1
	if  count == daoshu:
		break
