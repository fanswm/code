#!/bin/python
#-*-coding utf8-*-

import math

def is_prime(n):
	if n == 1 or n == 2:
		return True
	m = int(math.sqrt(n)) + 1
	f = True
	for i in range(2, m):
		if n % i == 0:
			f = False
			break
	return f

for j in range(100):
	if is_prime(j):
		print j,
	
print


