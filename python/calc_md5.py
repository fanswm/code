#!/bin/python
#-*- coding: utf-8 -*-

import hashlib

publicstr = r'abc'

def calc_md5(password):
	md5 = hashlib.md5()
	md5.update(password + publicstr)
	return md5.hexdigest()

db = {
	'jack': 'e10adc3949ba59abbe56e057f20f883e',
	'bob': 'cabd625b601af3c1101e95b8178e4337',
	'alice': 'e99a18c428cb38d5f260853678922e03'
}

def login(user, password):
	if db.has_key(user):
		savedmd5 = db[user]
	else:
		print "Sorry! this user is not exist!"
		return None
	md5 = hashlib.md5()
	md5.update(password + publicstr)
	if savedmd5 == md5.hexdigest():
		print 'passed!'
	else:
		print 'wrong password!'

def sign_in(user, password):
	if db.has_key(user):
		print 'Sorry, this user: %s has exist!' %user
		return None
	else:
		db[user] = calc_md5(password + publicstr)
		print 'good! you have signed by username: %s' %user

sign_in('abc', '876543210')

print calc_md5('876543210')

login('bob', r'876543210')