import functools
def log(text):
    if isinstance(text,str):
        def decorator(func):
            @functools.wraps(func)
            def wrapper(*args,**kw):
                print 'begin call %s:'%text
                func(*args,**kw)
                print 'end call %s:' %text
            return wrapper
        return decorator
    else:
        @functools.wraps(text)
        def wrapper(*args,**kw):
                print 'begin call %s:'%text.__name__
                text(*args,**kw)
                print 'end call %s:' %text.__name__
        return wrapper


@log
def f1():
    print 'f1ing'
@log('excute')
def f2():
    print 'f2ing'

f1()
f2()