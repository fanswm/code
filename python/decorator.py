#!/bin/python
#-*-coding utf8-*-

import functools

def t(*text):
	def de(func):
		@functools.wraps(func)
		def wrapper(*args, **kw):
			for i in text:
				print i,
			print "call start: %s" %func.__name__
			return func(*args, **kw)
		return wrapper
	return de
	
def log(func):
	@functools.wraps(func)
	def wrapper(*args, **kw):
		print "begin call"
		func(*args, **kw)
		print "end call."
	return wrapper

@t()
def now():
	print "2016-10-26"

@t("zdhr")
def now2():
	print "2016-10-27"

now()
print "Check now.__name__ = %s" % now.__name__	
now2()
print "Check now2.__name__ = %s" % now2.__name__


'''
def log2(text):
	def decorator(func):
		@functools.wraps(func)
		def wrapper(*args, **kw):
			print "%s is call %s()" %(text, func.__name__)
			return func(*args, **kw)
		return wrapper
	return decorator

@log2("by fanswm:")
def now2():
	print "2016-10-27"
	
now2()	

print "now2().name = %s" % now2.__name__
'''
