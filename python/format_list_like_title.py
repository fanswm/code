#!/bin/python
#-*-coding utf8-*-
def f(s):
    r=""
    r = r + s[0].upper()
    for i in s[1:]:
        r = r + i.lower()
    return r

def f1(ll):
    return map(f,ll)

print f1(['adam', 'LISA', 'barT'])


