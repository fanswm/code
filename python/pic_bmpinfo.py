#!/usr/bin/env python3
# -*_ coding:utf-8 -*-
# 判断是否位图，如果是，返回信息：
import os, struct

def bmpinfo(file_path):
    with open(file_path,'rb') as f:
        s = f.read(30)
    a = struct.unpack('<ccIIIIIIHH', s)
    if a[0]+a[1] == b'BM':
        print("The file: %s is a bmp, %d * %d, color: %d" \
              %(file_path, a[6], a[7], a[9]))
        return True
    else:
        print("The file %s is not a bmp." % file_path)
        return False
    
if __name__ == '__main__':
    bmpinfo('./222.bmp')
