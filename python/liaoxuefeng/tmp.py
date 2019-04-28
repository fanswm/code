def num_gen():#自然数迭代器
    n=1
    while True:
        yield n
        n=n+1

def hui_gen():#回数迭代器
    it=num_gen()
    it = filter(lambda x:str(x)==str(x)[::-1], it)
    while True:
        yield next(it)

for n in hui_gen():#测试
    if n<1000:
        print(n)
    else:
        break
