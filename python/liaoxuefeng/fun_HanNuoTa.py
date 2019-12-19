#coding: utf-8
def hannuota(n, a, b, c):
    if n == 1:
        print(a, '-->', c)
    else:
        hannuota(n-1, a, c, b)
        print(a, '-->', c)
        hannuota(n-1, b, a, c)
'''
递归函数的伪算法为如下:
if(n == 1)
   直接将A柱子上的圆盘从A移动到C
else
   先将A柱子上的n-1个圆盘借助C柱子移动到B柱子上
   直接将A柱子上的第n个圆盘移动到C柱子上
   最后将B柱子上的n-1个圆盘借助A柱子移动到C柱子上
该递归算法的时间复杂度为O（2的n次方)，当有n个圆盘时，需要移动圆盘2的n次方-1次
'''

hannuota(3, 'A','B','C')
