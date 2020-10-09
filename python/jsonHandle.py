#!/bin/python
# coding: utf-8

def main():
	f = open("input.json","r+", encoding='UTF-8')
	# f = open("goodsList.json","a+")
	
	# for i in range(10):
	# 	f.write("This is line %d\r\n" % (i+1))
		
	# f.close()
	
	# Open the file back and read the contents
	# f=open("goodsList.json", "r")
	# if f.mode == 'r+':
	# 	contents = f.read()
		
	# print(contents)
	
	# or, readlines reads the individual line into a list
	fl = f.readlines()
	for x in fl:
		old = x.partition(":")
		if(old[0].isalnum()):
			newLine = '"' + old[0] + '"' + old[1] + old[2]
		else:
			newLine = old[0] + old[1] + old[2]

		print(newLine.strip())
		
if __name__== "__main__":
	main()
