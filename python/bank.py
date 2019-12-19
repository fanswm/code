import re

MAX_EXCHANGE =100

def is_number(s):
    pattern = re.compile(r'^[-+]?[-0-9]\d*\.\d*|[-+]?\.?[0-9]\d*$')
    result = pattern.match(s)
    if result:
        return True
    else:
        return False

def input_type(string):
    flag = 0
    if is_number(string): 
        flag = 1
    elif string.isalpha():
        flag = 2
    else:
        flag = 0 # input_error
    return flag

def is_positive_number(f):
    return f>0 

def input_error():
    print("小精灵：您输入的选项，臣妾做不到哎！")

def is_yes_no(i):
    if input_type(i) == 2:
        if i == 'yes' or i == 'no' or i == '是' or i == '不':
            return 1
    return 0

def pay_error(pay, money):
    x = pay - money
    if x >= 0.01:
        print("小精灵：都说你们中国多壕，也不要这么大方嘛！您给多了，我再找您：%0.2f 元人民币。" %x ) 
        return 0
    elif x > 0 and x < 0.01: 
        print("小精灵：请收下您的%0.2f 金加隆." % number)
        return 0
    else: 
        print("小精灵：您这是欺负我不识数吗？请再给%0.3f人民币！" % -x )
        return 1 # 返回1代表支付错误

def call_police(ex_number):
    print("小精灵：您已经兑了%d金加隆了，还不够吗！！！\n\t经理！！！有人挤兑闹事儿！！！\n\t......" % ex_number)
    print("警车正在开来...")

def refuse_exchange(number, ex_num, times):
    # 返回是否拒绝兑换：1: 允许
    # 想要兑换的金额number， 已经兑换的金额ex_num， 在被拒绝后重复要求的次数times
    if number + ex_num > MAX_EXCHANGE:
        print("小精灵：您的兑换金额：%0.2f 金加隆 不被允许；" %number)
        print("\t您只能兑换%0.2f 金加隆。" % (MAX_EXCHANGE - ex_num))
        print("请重新输入您的金额.")
        if times >=3:
            call_police(ex_num)
        return 0
    else:
        return 1

def allow_exchange(ex_number):
    # 如果允许兑换：返回可以兑换多少钱
    num_for_ex = MAX_EXCHANGE- ex_number
    if num_for_ex > 0.01:
        print("小精灵：您还可以兑换 %0.2f 金加隆." % num_for_ex)
        return num_for_ex
    else:
        return 0.0

def for_exchange():
    # 返回要求兑换多少钱？
    print("小精灵：金加隆和人民币的兑换率为1:51.3，\n\t即'1金加隆=51.3人民币'.")
    i = input("\t请问您要兑换多少 金加隆 呢？（请输入您想兑换的数额）：\n>>")
    while input_type(i) != 1 or not is_positive_number(float(i)):
        input_error()
        print("输入错误，请输入数字且是正数。")
        i = input("\t请问您要兑换多少 金加隆 呢？（请输入您想兑换的数额）：\n>>")

    num = float(i)
    print("小精灵：好的，我知道了，您需要兑换 %0.2f 金加隆。" % num)

    return num


def exchange(number, ex_num, times):
    # 想要兑换多少钱；已经兑换了多少钱; 以前要求过的次数;
    # 返回本次支付多少钱

    money = number * 51.3
    pay = 0
    print("\t那么，您需要付给我%0.2f人民币." % money)
    i = input("请给我钱吧：\n>>")
    while input_type(i) != 1 or not is_positive_number(float(i)):
        i = input("请输入数字且是正数\n>>")

    print("exchange 1")
    p = float(i)
    pay += p

    while pay_error(pay, money): # 支付不足
        i = input("支付不足，请给钱：\n>>")
        while input_type(i) != 1 or not is_positive_number(float(i)):
            i = input("请输入数字且是正数\n>>")

        print("exchange 2")
        p = float(i)
        pay += p

    return pay

def eexit(number,ex_number, times, exit):
    # 想要兑换多少钱；ex_number: 已经兑换的金额；exit= 'yes' or 'no'
    # 返回本次支付金额
    if is_yes_no(exit):
        if exit == 'no' or exit == '是':
            return exchange(number, ex_number, times)
        elif exit == 'yes' or exit == '不':
            print("小精灵：感谢您的光临！欢迎再来！")
            return 0.0

    input_error()
    return 0.0

number = 0
ex_number = 0
times = 0

choice = input("小精灵：您好，欢迎来到古灵阁!\n\t请问您需要帮助吗？需要or不需要？i\n\t(请输入'yes' 或 'no'):\n>>")
while input_type(choice) != 2 or not is_yes_no(choice):
    input_error()
    print("请输入'yes' ro 'no'。")
    choice = input("小精灵：您好，欢迎来到古灵阁!\n\t请问您需要帮助吗？需要or不需要？i\n\t(请输入'yes' 或 'no'):\n>>")

if choice == "yes" or choice == '是':
    i = input("小精灵：请问您需要什么帮助呢？\n\t1 存取款；2 货币兑换；3 咨询\n>>")
    while i != '1' and i != '2' and i != '3':
        input_error()
        print("请输入1，2，3")
        i = input("小精灵：请问您需要什么帮助呢？\n\t1 存取款；2 货币兑换；3 咨询\n>>")
    what = int(i)

    if what == 1:
        print("小精灵:推荐您去1号存取款窗口!\n\tBye!")
    elif(what == 2):
        if refuse_exchange(number, ex_number, times): # 如果允许兑换
            allow_exchange(ex_number)
            if times > 3:
                call_police(ex_number)
            else:
                for_ex_num = for_exchange()
                if refuse_exchange(for_ex_num, ex_number, times): # 如果允许兑换
                    exchange(for_ex_num, ex_number, times)
                    ex_number += for_ex_num
                else:
                    times += 1
        else:
            time += 1
            print(times)

        exit = input("小精灵：您是否dd要离开？请回答'yes' or 'no':\n>> ")
        while not is_yes_no(exit):
            input_error()
            print("请重新输入yes or no。")
            exit = input("小精灵：您是否dd要离开？请回答'yes' or 'no':\n>> ")

        if exit == 'no' or exit == '不':
            while exit == 'no' or exit == '不':
                allow_exchange(ex_number)
                if times > 3:
                    call_police(ex_number)
                else:
                    for_ex_num = for_exchange()
                    if refuse_exchange(for_ex_num, ex_number, times): # 如果允许兑换
                        eexit(for_ex_num, ex_number, times, exit)
                        ex_number += for_ex_num
                    else:
                        times += 1
                        print(times)

                exit = input("小精灵：您是否要离开？请回答'yes' or 'no':\n>> ")
                while not is_yes_no(exit):
                    input_error()
                    print("请重新输入yes or no。")
                    exit = input("小精灵：您是否要离开？请回答'yes' or 'no':\n>> ")
        else:
            eexit(0.0, ex_number, times, exit)
    elif what == 3:
        print("小精灵：请您去3号咨询窗口！\nBye!")
else: # 'no' or '不'
    print("小精灵：你把我吵醒却没事儿，你这是来逗老娘的吗？g u nnnnn!")

print("程序结束！")
