#!/bin/python
#coding: utf-8

import os
import requests
path=os.getcwd()+'\\imgs\\'
import pandas as pd
df=pd.read_excel('urlList.xlsx')

urls=df.url
for i in range(len(urls)):
	print(i)
	r = requests.request('get',urls[i])
	print(r.status_code)

	with open(path+str('img')+str(i)+'.jpg','wb') as f:
		f.write(r.content)
	f.close()
