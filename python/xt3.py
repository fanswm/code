#!/bin/python
#-*-coding utf8-*-

def count():
	fs = []
	for i in range(1,4):
		fs.append((lambda j: lambda: j*j)(i))
	return fs

f1, f2, f3 = count()
print f1(), f2(), f3()