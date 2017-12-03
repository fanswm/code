#!/usr/bin/python
# Filename: math_game.py

import sys

try:
	import cPickle as p
except:
	import pickle as p

'''
#!/usr/bin/python
# Filename: pickling.py

import cPickle as p
#import pickle as p

shoplistfile = 'shoplist.data'
# the name of the file where we will store the object

shoplist = ['apple', 'mango', 'carrot']

# Write to the file
f = file(shoplistfile, 'w')
p.dump(shoplist, f) # dump the object to a file
f.close()

del shoplist # remove the shoplist

# Read back from the storage
f = file(shoplistfile)
storedlist = p.load(f)
print storedlist 
'''
#这个程序在当前文件夹内创建myadd.txt文件

class addbook(object):
	'''
	docstring for addbook.
	'''
	head = ('name', 'sex', 'phone', 'othertel',\
		'company', 'houseaddress','id_card', 'remarks')
	a_b_dict = {}		# 程序运行期间存入的每一条记录，格式：{‘name’:['sex','phone'...], 'name1':...}
	a_b_item_set = set()	# 程序运行期间存入的每一条记录的姓名

	def _commit_to_dict(self):	# 初始化一条记录，提交到a_b_dict, a_b_item_set
		tmp_dict = {}
		tmp_list = []

		for name, value in vars(self).items():
			tmp_dict[name] = value	# 把每一个参数的名字和其值（无序）存入tmp_dict

		for i in self.head:
			if i == 'name':		# 如果是姓名，pass
				pass	
			else:
				tmp_list.append(tmp_dict[i])	# 如果是这个人的信息，则存入tmp_list
		self.a_b_dict[tmp_dict['name']] = tmp_list	# 姓名存入self.a_b_dict的key
		self.a_b_item_set.add(str(tmp_dict['name']))	# 把每一个姓名存入a_b_item_set
		# print self.a_b_dict
		# print self.a_b_item_set
	
	def __init__(self, name, sex, phone, othertel,\
		company, houseaddress, id_card, remarks):
		self.name = name
		self.sex = sex
		self.phone = phone
		self.othertel= othertel
		self.company = company
		self.houseaddress = houseaddress
		self.id_card = id_card
		self.remarks = remarks

		self._commit_to_dict()	# 把记录本提交到self.a_b_dict

	def find_phonenum(self, phonenum):
		for name in self.a_b_dict:
			if self.a_b_dict[name][1] == phonenum:
				return name
	def find_name(self, fname):
		for name in self.a_b_dict:
			if name == fname:
				return self.a_b_dict[name][1]
		
class a_b_file(addbook):
	'''
	docstring for a_b_file.
	'''
	file_dict = {}
	file_set = set()	# 从已有文件读入的每一条姓名的记录存入此
	def __init__(self, abk, filename):
		# super(a_b_file, self).__init__()
		self.abk = abk
		self.filename = filename

		self._write_to_file_init()
		self._add_recorder_to_file()
		self._load_file_to_dict()

	def _write_to_file_init(self):		
		'''
		如果filename文件已有：添加；若无，创建，添加。
		'''
		flen = 0
		try:
			f = open(self.filename, 'r')
			flen = len(f.read(20))
		except:
			f = open(self.filename, 'w')
			f.close()
			f = open(self.filename, 'r')
			flen = len(f.read(20))
		finally:
			f.close()

		f = open(self.filename, 'a')
		if flen == 0:
			for i in self.abk.head:
				f.write(i)
				f.write('\t')
			f.write('\n')
		else:
			pass
		f.close()

	def _add_recorder_to_file(self):		
		f = open(self.filename, 'r')
		for line in f:
			j = 0
			s = ''
			for i in line:
				while line[j] != '\t':
					s = s + line[j]
					# print line[j],
					j += 1
			# print s
			self.file_set.add(s)		
		diff_set = self.file_set & self.abk.a_b_item_set	# 已有set 与 本次提交的set 共有的名字
		diff_set = self.abk.a_b_item_set - diff_set		# 新提交的 姓名
		f.close()

		f = open(self.filename, 'a')
		for a in diff_set:
			for b in self.abk.a_b_dict:
				if a == b:
					f.write(a)
					f.write('\t')
					for b in self.abk.a_b_dict[a]:
						f.write(str(b))
						f.write('\t')
					f.write('\n')
		f.close()

	def _load_file_to_dict(self):
		it = []
		i = 0
		f = open(self.filename, 'r')
		f.readline()	# 跳过文件首
		for line in f:
			it = self._line_of_file_to_list(line, '\t', '\n')
			self.file_dict[it[0]] = it[1:]
		print self.file_dict

	def _line_of_file_to_list(self, line, sep, end):
		line_list = []
		i = 0
		while line[i] != end:
			s = ''
			while line[i] != sep:
				s += line[i]
				i += 1
			i += 1 	# 跳过sep
			line_list.append(s)
		return line_list

	def del_name_from_file(self, delname):
		have = 0
		if delname in self.file_dict:
			have = 1
			del(self.file_dict[delname])
			self.file_set.discard(delname)
		if delname in self.abk.a_b_dict:
			have = 1
			del(self.abk.a_b_dict[delname])
			self.abk.a_b_item_set.discard(delname)
		if have == 0:
			print 'del name: %s failed!'

myadd = addbook('fanswm', 'm', '15031164531', None, 'HR', 'ZD', '13010319', 'a man')
myadd = addbook('wuxian', 'w', 18232185120, None, 'HW', 'ZD', '13012', 'My wife')
myadd = addbook('fanxizhe', 'm', '150311', None, None, None, None, 'My son')

myadf = a_b_file(myadd, 'myadd.txt')
