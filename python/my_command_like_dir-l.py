#!/usr/bin/env python3
# coding: utf-8

'''
like command:'dir -l'
未完成的：
	总用量；
	第一列的文件标识符 d,l,-
注意：
	我在当前文件夹模仿建立了一个/etc/passwd文件
	用于Linux系统
'''
__author__ = 'abstracthex@163.com'

import os, time

rwx = {'7':'rwx','6':'rw-','5':'r-x','4':'r--','2':'-w-','1':'--x','0':'---'}

def get_rwx(rwx_num_str):
	s = ''
	for i in rwx_num_str:
		s += rwx[i]
	return s

def get_uid_gid(file_passwd_path):
	uid = {}
	gid = {}
	with open(file_passwd_path, 'r') as f:
		for line in f.readlines():
			l = line.strip().split(':')
			if len(l) > 2:
				uid[l[2]] = l[0]
				gid[l[3]] = l[0]

	return uid,gid

uid, gid = get_uid_gid('./passwd')

def get_file_stat(file_path, uid,gid):
	s = ''
	f_stat = os.stat(file_path)

	s += get_rwx(oct(f_stat.st_mode)[-3:])
	s += '\t'
	s += uid[str(f_stat.st_uid)]
	s += '\t'
	s += gid[str(f_stat.st_gid)]
	s += '\t'
	s += str(f_stat.st_size)
	s += '\t'
	s += time.strftime("%b %d %H:%M", time.localtime(f_stat.st_ctime))
	s += '\t'
	s += os.path.split(file_path)[1]

	return s

def main(path):
	f_list = os.listdir(path)

	for f in f_list:
		cur_path = os.path.join(path, f)
		print(get_file_stat(cur_path, uid, gid))

if '__name__' == '__main__':
	main('./')
