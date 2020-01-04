#!/usr/bin/env python3
# coding: utf-8

import re
from enum import Enum

'''
假如你来到了古灵阁，想用人民币兑换金加隆，汇率为：1 金加隆 = 51.3 人民币
小精灵向你打招呼，是否需要服务，如果需要，输入yes
否则，她会不高兴。

如果需要服务，请选择服务窗口，2 号是兑换窗口。
如果选择其他，会导航你去其他窗口。

输入兑换数量，最大兑换数量为MAX_EX_MONEY；
最大兑换次数为4
最大支付错误次数为3
'''
__author__ = 'abstracthex@163.com'


class Num(Enum):

	MAX_EX_MONEY  	= 100	# Num.MAX_EX_MONEY.value
	MAX_EX_TIMES	= 4		# Num.MAX_EX_TIMES.value
	MAX_PAY_TIMES	= 3		# Num.MAX_PAY_TIMES.value
	RATE 			= 51.3	# Num.RATE.value

class Bank(object):
	def __init__(self):
		self._exchanged_number = 0	# 累计兑换了多少
		self._exchanged_times = 0	# 累计兑换次数

		self._apply_money = 0		# 本次申请兑换多少钱 开放
		self._success_money = 0		# 本次申请成功多少钱 开放

		self._pay = 0				# 本次需要支付多少钱
		self._paying = 0			# 本次正在支付多少钱 开放
		self._payed = 0				# 本次累计已经支付了多少
		self._paying_times = 0		# 本次支付次数

		self._user_name = ''		# 开放

	@property
	def exchanged_number(self):
		return self._exchanged_number

	@property
	def exchanged_times(self):
		return self._exchanged_times

	@property
	def success_money(self):
		return self._success_money

	@property
	def apply_money(self):
		return self._apply_money

	@apply_money.setter
	def apply_money(self, value):
		self._apply_money = value

	@success_money.setter
	def success_money(self, value):
		self._success_money = value
		if self._paying_times > Num.MAX_PAY_TIMES.value:
			self._exchanged_number -= self._success_money
		else:
			self._exchanged_number += value
		
		if value > 0:
			self._exchanged_times += 1

		self._pay = value * Num.RATE.value

	@property
	def pay(self):
		return self._pay

	@property
	def paying(self):
		return self._paying

	@paying.setter
	def paying(self, value):
		self._paying = value
		self._payed += value
		self._paying_times += 1

	@property
	def payed(self):
		return self._payed

	@property
	def paying_times(self):
		return self._paying_times	

	@property
	def user_name(self):
		return self._user_name

	@user_name.setter
	def user_name(self, string):
		self._user_name = string

	@property
	def bank_pay(self):
		self.success_money = 0
		self.paying = 0
		self._payed = 0
		self._paying_times = 0

	@property
	def bank_pay_times_overflow(self):
		self._exchanged_number -= self._success_money
	
class Input_issue(object):

	def is_number(self, string):
		pattern = re.compile(r'^[-+]?[-0-9]\d*\.\d*|[-+]?\.?[0-9]\d*$')
		return pattern.match(string)
	
	def input_type(self, string):
		if self.is_number(string): 
			flag = 1	# 数字
		elif string.isalpha():
			flag = 2	# 字母
		else:
			flag = 0 	# 错误
		return flag

	def is_positive_number(self, f):
	    return f>0 

	def is_yes_no(self, i):
		if self.input_type(i) == 2:
			if i == 'yes' or i == 'no' or i == '是' or i == '不':
				return True
		return False

class Bank_voice(Bank):
	@property
	def voice_allow_apply(self):
		print("小精灵：您的兑换金额不被允许，您已经兑换了 %d 金加隆，目前还能兑换 %d 金加隆。" \
			%(self.exchanged_number, Num.MAX_EX_MONEY.value - self.exchanged_number))

	@property
	def voice_welcome(self):
		print("小精灵：%s 您好，欢迎来到古灵阁!\n\t请问您需要帮助吗？需要or不需要？i\n\t(请输入'yes' 或 'no')" % self.user_name)

	@property
	def voice_welcome_back(self):
		print("小精灵：%s , 欢迎再来！" % self.user_name)

	@property
	def voice_gun(self):
		print("小精灵：你把我吵醒却没事儿，你这是来逗老娘的吗？g u nnnnn!")

	@property
	def voice_what_service(self):
		print("小精灵：请问您需要什么帮助呢？1 存取款；2 货币兑换；3 咨询\n\t请输入数字（1，2, 3）")

	@property
	def voice_i_cannot(self):
		print("小精灵：您输入的选项，臣妾做不到哎！")

	@property
	def voice_exchange_description(self):
		print("小精灵：金加隆和人民币的兑换率为1:51.3")

	@property
	def voice_how_many(self):
		print("小精灵：请输入您想兑换的金额:")

	@property
	def voice_input_error(self):
		print("小精灵：您的输入有误！请重新输入：")

	@property
	def voice_exchange_again(self):
		print("小精灵：您要继续兑换吗？请输入 yes or no.")

	@property
	def voice_china_tuhao(self):
		print("小精灵：都说你们中国多壕，也不要这么大方嘛！")

	@property
	def voice_call_police(self):
		if self.exchanged_number >= Num.MAX_EX_MONEY.value:
			print("小精灵：你都已经兑换了 %d 金加隆了！还不够吗？经理，有人闹事儿！\n\t警车正在开来..." %self.exchanged_number)
		else:
			print("小精灵： 虽然你才兑换了 %d 金加隆，但是你正在兑换 第%d次，超过了兑换次数：%d次。\n\t警车下在开来..." \
				%(self.exchanged_number,self.exchanged_times, Num.MAX_PAY_TIMES.value))
	@property
	def voice_let_pay(self):
		print("小精灵：您将兑换 %d 金加隆，请支付 %0.2f 人民币！" %(self.success_money, self.pay))

	def voice_other_windows(self, number):
		print("小精灵：请去 %d 窗口咨询！" %number)

	@property
	def voice_pay_big(self):
		print("小精灵：你给多了，再找您 %0.2f 人民币！" % (self.payed - self.pay))

	@property
	def voice_pay_not_enough(self):
		print("小精灵：你是欺负我不识数吗！再给我 %0.2f 人民币。" % (self.pay - self.payed) )
	
	@property
	def voice_pay_success(self):
		print("小精灵：支付成功！请收下 %d 金加隆。" % self.success_money)

	@property
	def voice_pay_times_overflow(self):
		print("小精灵：你已经尝试支付了%d次，超过了规定次数：%d次！交易失败。\n\t现退款给你 %0.2f 人民币！再见 " \
			% (self.paying_times, Num.MAX_PAY_TIMES.value, self.payed))

	@property
	def voice_please_input_positive(self):
		print("小精灵：请输入数字且是正数！请重新输入：")

	@property
	def voice_bank_refund(self): # 支付太多而退款
		print("小精灵：请收下退款： %0.2f 人民币。" % (self.payed - self.pay))

class Bank_exchange(Bank_voice, Input_issue):
	@property
	def display(self):
		print("\t\t\texchanged_number = %d\n\
			exchanged_times\t = %d\n\
			apply_money\t = %d\n\
			allow_money\t = %d\n\
			success_money\t = %d\n\
			pay\t\t = %0.2f\n\
			paying\t\t = %0.2f\n\
			paying_times\t = %0.2f\n\
			payed\t\t = %0.2f\n\
			pay_other\t = %0.2f\n\n" %(self.exchanged_number,self.exchanged_times,\
				self.apply_money,Num.MAX_EX_MONEY.value - self.exchanged_number,self.success_money,self.pay,\
				self.paying,self.paying_times, self.payed,self.pay - self.payed ))

	@property
	def get_input(self):
		self._get_input = input(">>")
		return self._get_input

	@property
	def pay_issue(self):
		x = self.payed - self.pay
		if x >= 0.01:
			return 1			# 支付太多
		elif x >= 0 and x < 0.01: 
			return 0			# 支付成功
		else:
			return -1			# 支付不足

	@property
	def pay_times_not_overflow(self):
		if self.paying_times <= Num.MAX_PAY_TIMES.value:
			return True
		else:
			self.voice_call_police
			return False	

	@property
	def allow_apply(self):
		# 返回是否拒绝兑换：1: 允许
		x = Num.MAX_EX_MONEY.value - self.exchanged_number - self.apply_money
		if x < 0:
			return False
		else:
			if self.exchanged_times > Num.MAX_EX_TIMES.value:
				self.voice_call_police
				return False
			else:
				return True

	@property
	def apply_exchange(self):
		# 返回成功申请兑换多少钱？
		self.voice_exchange_description
		self.voice_how_many

		i = self.get_input		#请输入金额

		while self.input_type(i) != 1 or not self.is_positive_number(float(i)):
			self.voice_input_error	#输入的不是数字，或不是正数
			self.voice_how_many		#你要兑换多少钱
			i = self.get_input

		self.apply_money = float(i)

		#如果兑换金额不被允许：
		while not self.allow_apply:
			self.voice_allow_apply
			self.voice_how_many

			i = self.get_input
			while self.input_type(i) != 1 or not self.is_positive_number(float(i)):
				self.voice_input_error	#输入的不是数字，或不是正数
				self.voice_how_many		#你要兑换多少钱
				i = self.get_input

			self.apply_money = float(i)

		self.success_money = self.apply_money

def user_paying(user):
	i = user.get_input
	#如果输入的不是数字且不是正数
	while user.input_type(i) != 1 or not user.is_positive_number(float(i)):
		user.voice_please_input_positive
		i = user.get_input

	#正在支付多少钱
	user.paying = float(i)

	while user.pay_issue == -1:	#如果支付不足
		while user.paying_times <= Num.MAX_PAY_TIMES.value: # 如果没有超过支付次数
			user.voice_pay_not_enough
			i = user.get_input
		
			while user.input_type(i) != 1 or not user.is_positive_number(float(i)): #如果输入的不是正数
				user.voice_please_input_positive
				i = user.get_input

			user.paying = float(i)
			if user.pay_issue >= 0:
				break
		if user.paying_times > Num.MAX_PAY_TIMES.value:
			break
	#到这里，如果正常支付，不存在支付不足的情况

	if user.paying_times <= Num.MAX_PAY_TIMES.value :
		#如果给钱给多了：
		if user.pay_issue == 1:
			user.voice_china_tuhao
			user.voice_pay_big
			user.voice_bank_refund
		user.voice_pay_success
	else:
		user.bank_pay_times_overflow
		user.voice_pay_times_overflow
	
def exchange(user):
	user.apply_exchange
	user.voice_let_pay
	user_paying(user)
	user.bank_pay

def exchange_again(user):
	user.voice_exchange_again
	
	i = user.get_input
	# 如果输入的不是 yes or no:
	while not user.is_yes_no(i):
		user.voice_i_cannot
		user.voice_input_error
		user.voice_exchange_again
		i = user.get_input

	while i == "yes" or i == "是":
		if user.allow_apply:
			exchange(user)
			user.voice_exchange_again

			i = user.get_input
			while not user.is_yes_no(i):
				user.voice_i_cannot
				user.voice_input_error
				user.voice_exchange_again
				i = user.get_input
		else:
			user.voice_allow_apply
			break
	
def bank_main(user):
	user.voice_welcome
	choice = user.get_input
	while user.input_type(choice) != 2 or not user.is_yes_no(choice):		
		user.voice_i_cannot
		user.voice_input_error
		choice = user.get_input

	if choice == "yes" or choice == '是':
		user.voice_what_service
		i = user.get_input

		while i != '1' and i != '2' and i != '3':
			user.voice_i_cannot
			user.voice_input_error
			user.voice_what_service
			i = user.get_input

		what = int(i)
		if what == 2:
			exchange(user)
			exchange_again(user)
			user.voice_welcome_back
		else:
			user.voice_other_windows(what)
			user.voice_welcome_back
	else:
		user.voice_gun

	print("程序结束！")

	    	
if __name__ == '__main__':
	user = Bank_exchange()
	user.user_name = "Tom"
	bank_main(user)

	