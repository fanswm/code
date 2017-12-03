#!/usr/bin/python
# coding: utf-8
# Filename: math_game.py

#from ctypes import *

#i = c_int(5)
#i.value = 10

#randdll = CDLL('pythonrand.dll')

import random

s = raw_input('今天，你想做几道题呢？请输入道数:')
daoshu = int(s)

count = 0
while True:
    a = random.randint(99, 999)

    if a > 900:
        b = random.randint(99, 999)
        if a > b:
            sum = a - b
            print a, '-', b,
        else:
            sum = a + b
            print a, '+', b,
    else:
        b = random.randint(0, (1000 - a))
        sum = a + b
        print a, '+', b,
        
    c = random.randint(99, 999)

    if sum == (a + b):
        if sum < c:
            sum += c
            print '+', c, '=',
        else:
            sum -= c
            print '-', c, '=',
    else:
        c = random.randint(99, 999)
        if c > sum:
            sum += c
            print '+', c, '=',
        else:
            sum -= c
            print '-', c, '=',

    s = raw_input()
    d = int(s)

    if d == sum:
        print '真棒！'
    else:
        print 'NO NO NO! 答案是:', sum
            
    count += 1
    if  count == daoshu:
        break
