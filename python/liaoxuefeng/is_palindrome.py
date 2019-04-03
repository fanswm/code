# coding: utf-8

STRING={0:'0',1:'1',2:'2',3:'3',4:'4',5:'5',6:'6',7:'7',8:'8',9:'9'}

def int2str(n):
    s=''
    while n % 10 > 0:
        a = divmod(n,10) 
        s = STRING[a[1]] + s
        n = a[0]

print(int2str(12345))

def is_palindrome(n):
    pass
