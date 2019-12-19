#coding: utf-8
def fact_n(n,pro):
    if n == 1:
        return pro 
    return fact_n(n-1, n * pro)

def fact(n):
    return fact_n(n,1)

print(fact(3))

