#!/bin/python
#-*-coding utf8-*-

max = 1
m = 0
n = 0
for i in range(9):
	for j in range(max):
		sum = (i + 1) * (j + 1)
		print "%2d *%2d = " %(j+1, i+1),
		s = raw_input()
		c = int(s)
		print
		if c != sum:
			print "\tThe answer is: %s" % sum
			n += 1
		else:
			print "\tOk!"
			m += 1
	max = max + 1
	print

print "Total: %s\n\tRight: %s\tError: %s\n" %(m + n, m, n)
