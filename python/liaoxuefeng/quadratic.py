#!/bin/python
# -*- coding: utf-8 -*-

import math

def quadratic(a, b, c):
	if not isinstance(a, (int, float)):
		raise TypeError('bad operand type')
	if not isinstance(b, (int, float)):
		raise TypeError('bad operand type')
	if not isinstance(c, (int, float)):
		raise TypeError('bad operand type')
		
	dlt = b * b - 4 * a * c
	if dlt > 0:
		r1 = (-b + math.sqrt(dlt)) * 0.5 / a
		r2 = (-b - math.sqrt(dlt)) * 0.5 / a
		#print("diff result: %f; %f" %(r1, r2))
		return r1, r2
	elif dlt == 0:
		r1 = -b * 0.5 / a
		return r1, r1
	else:
		#print("No real result!")
		return None, None

# 测试:
print('quadratic(2, 3, 1) =', quadratic(2, 3, 1))
print('quadratic(1, 3, -4) =', quadratic(1, 3, -4))

if quadratic(2, 3, 1) != (-0.5, -1.0):
	print('测试失败')
elif quadratic(1, 3, -4) != (1.0, -4.0):
	print('测试失败')
else:
	print('测试成功')
