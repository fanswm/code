#!/bin/python
#-*-coding utf8-*-
def dropfstandlst(grades):
	first, *middle, last = grades
	return avg(middle)
	
g = [1,2,3,4,5]

print (dropfstandlst(g))

