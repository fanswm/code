#!/bin/python
# coding: utf-8
def trim(s):
	i1 = 0
	if s == '':
		tmp = ''
	else:
		tmp = s[0]
	while tmp == ' ':
		i1 += 1
		tmp = s[i1:(i1 + 1)]

	i2 = -1
	tmp = s[-1:]
	while tmp == ' ':
		i2 -= 1
		tmp = s[i2:(i2 - 1)]

	print(s[i1:i2])
	#print("i1 = %d, i2 = %d" %(i1, i2))
	if i2 == -1:
		return s[i1:]
	else:
		return s[i1:i2]


	
	
	print("len(s)= %d" %(len(s)))
	
if trim('hello  ') != 'hello':
	print('测试失败!')
elif trim('  hello') != 'hello':
	print('测试失败!')
elif trim('  hello  ') != 'hello':
	print('测试失败!')
elif trim('  hello  world  ') != 'hello  world':
	print('测试失败!')
elif trim('') != '':
	print('测试失败!')
elif trim('    ') != '':
	print('测试失败!')
else:
	print('测试成功!')
    
