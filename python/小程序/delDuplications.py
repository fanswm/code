#!/bin/python3
# coding: utf-8
'''
project 目录结构：
	miniprogram
		|-component
		|		|-me
		|			|-components
		|-pages
		|	|-index
		|	|-components
		|	|		|-home
		|	|		|-mine
		|	|details
		|	|...
		|-delDuplications.py
-------------------------------------
	delDuplications.py 必须在这个位置；
	无论是 component 还是 page 页面，定义的原则是：文件夹名就是组件名，或页面名
	自定义组件名如果叫 comp, 那么它在 wxml 中叫：me-comp
	[Bug]: 误删 masker; my-behavior;page-home(因为我没有按照这个原则定义)
'''
import os
import shutil # 删除文件夹
import re

def _findAllFFname(base, extName):
	# base 根文件夹，extName 扩展名
	for root, ds, fs in os.walk(base):
		for f in fs:
			if f.endswith(extName):
				fullName = os.path.join(root, f)
				yield fullName
				
def _findAllFname(base, extName):
	# base 根文件夹，extName 扩展名
	for root, ds, fs in os.walk(base):
		for f in fs:
			if f.endswith(extName):
				yield f

# 递归返回一个目录中，不带目录，不带扩展名的文件名
def findAllFname(base, extName):
	list = []
	for i in _findAllFname(base, extName):
		base = os.path.basename(i) # 不带路径，带扩展名的文件名
		fn = os.path.splitext(base)[0] # 不带目录，不带扩展名的文件名
		list.append(fn)
	return list
		
# 递归返回一个目录中全路径的文件名			
def findAllFFname(base, extName):
	list = []
	for i in _findAllFFname(base, extName):
		list.append(i)	# 每一个全路径文件名
	return list

# 获取子目录所有目录名称
def getChildDirName(base):
	L = []
	g = os.walk(base)
	for path, dir_list, file_lsit in g:
		for dir_name in dir_list:
			# dirn = os.path.join(path, dir_name) # 以 base 为基础的全路径
			# if L.count(dirn) == 0:
			# 	L.append(dirn)
			L.append(dir_name)
			
	return L

def get1JsonComps(fullName):
	'''
	读到一个 json 文件，把其中的 'me-component' 读出来, 返回 List
	json 文件的结构：
	{
		"component": true,
		"usingComponents": {
			"me-component": "../../../components/me/component/component",
		}
	}
	'''
	localeCompList = []
	f = open(fullName, 'r', encoding='UTF-8')
	try:
		for line in f:
			n1 = line.strip() # 删除空白符
			n2 = n1.split(':', 1)[0] # 取得 ":" 左边的部分
			# n3 = n2.rstrip(',')	# 删除字符串右边的 ","
			n4 = n2.strip('"'or "'")	# 删除字符串两边的 双引号 或 单引号, 得到 最终的文件名
			n5 = n4.lstrip('me-')
			localeCompList.append(n5)
	finally:
		f.close()
	return localeCompList

# 把 locale 中的每一项，从 source 中删除：	
def duplicationCompList(source, locale):
	for i in locale:
		try:
			source.remove(i)
		except ValueError:
			pass
	return source

# 获取 pages 目录中所有没有用到的组件名称：	
def getDuplicationsName(compPath, pagesPath):
	# 取得 '/components/me' 中所有的组件名称
	# source = findAllFname('./components/me', '.json') # 利用 components/me 中每一个子目录中的 json 文件名，获得所有的 组件名称
	
	source = getChildDirName(compPath) # 利用 components/me 中每一个子目录中名称，获得所有的 组件名称
	
	# 递归打开 '/pages/' 下的每一个 json 文件
	# 得到 '/components/me/' 在 '/pages/' 中没有用到的组件名称
	for f in _findAllFFname(pagesPath, '.json'):
		locale = get1JsonComps(f) # 获取这个文件中的所有的 comp 名称
		duplicationCompList(source, locale) # 把 locale 中所有的名称 从 source 中删除掉
		
	# 得到 '/components/me/' 在 '/pages/' 中没有用到,而且在 '/components/me/' 中也没有彡到 的组件名称	
	for f in _findAllFFname(compPath, '.json'):
		locale = get1JsonComps(f)
		duplicationCompList(source, locale)
	return source
	
	
def delDuplications(compPath, pagesPath):
	'''
	删除 compPath 中所有：
		pagesPath 中没有用到
		compPath 自身没有用到
	的 comp
	'''
	L = getDuplicationsName(compPath, pagesPath)
	for comp in L:
		dir_name = compPath + '/' + comp
		# dir_name = os.path.join(compPath, comp)
		shutil.rmtree(dir_name)
		
		
def getWxmlComps(fn):
	'''
	读到一个 Wxml 文件，把其中的 <comp> 读出来, 返回 List
	'''
	comps = []
	try:
		f = open(fn, 'r', encoding='UTF-8')
		try:
			s = re.split('\s|<|>', f.read())
			for i in s:
				i = i.strip('/')
				if i != '':
					comps.append(i.strip('/'))
		finally:
			f.close()
		return comps
	except:
		raise

# 从一个 json 文件中的一行，获取 comp 名称：
def jsonLineGetCompName(jsonLine):
	n1 = jsonLine.strip() # 删除空白符
	n2 = n1.split(':', 1)[0] # 取得 ":" 左边的部分
	n3 = n2.strip('"')	# 删除字符串两边的 双引号 或 单引号, 得到 最终的文件名
	n4 = n3.strip("'")	# 删除字符串两边的 双引号 或 单引号, 得到 最终的文件名
	return n4.lstrip('me-')
	
def compInJsonIsUsedInWxml(jsonFn, wxmlFn):
	'''
	jsonFn: .json 全路径文件名
	wxmlFn: .wxml 全路径文件名
	
	在同一目录下的读取： json 文件中定义的 comp 在 wxml 中使用则保留，否则删除
	把新文件重新写回
	'''
	wxmlComps = getWxmlComps(wxmlFn);
	try:
		f = open(jsonFn, 'r', encoding='UTF-8')
		lines = f.readlines()
		newJson = []
		invalidIndex = []
		for i in range(len(lines)):
			c = jsonLineGetCompName(lines[i]) # 从每一行中获取 组件名称
			if (c!='}' and c!='{' and c!='usingComponents' and c!='component'):
				jsonComp = 'me-' + c
				if jsonComp not in wxmlComps:
					invalidIndex.append(i) # 未使用的组件名称在 compList 中的 index
					
		for index in range(len(lines)):
			if index not in invalidIndex:
				newJson.append(lines[index])
		f.close()
		
		# 写入文件：
		f = open(jsonFn, 'w', encoding='UTF-8')	
		for i in newJson:
			f.write(i)
		f.close()
	except:
		raise
	
# 删除 '/pages/' 目录中的无用 component.	
def del_duplications_from_pages_dir_by_json():
	# 递归得到 'pages/' 目录中所有的文件名
	s = findAllFFname('./pages','.json')
	for i in s:
		path,fullName = os.path.split(i) #/dir/dir/f.ext :: /dir/dir/: f.ext 
		fname,ext = os.path.splitext(fullName) # f | .ext
		jsonFn = path + '\\' + fname + '.json'
		wxmlFn = path + '\\' + fname + '.wxml'
		
		compInJsonIsUsedInWxml(jsonFn, wxmlFn)
	

def main():
	del_duplications_from_pages_dir_by_json()
	delDuplications('./components/me', './pages')
	# compInJsonIsUsedInWxml('./pages/details/details.json', './pages/details/details.wxml')
	
	# s = findAllFFname('./pages','.json')
	# for i in s:
	# 	print(i)
	
	# s = getWxmlComps('./pages/index/index.wxml')
	# print(s)
	
	
		
if __name__ == '__main__':
	main()