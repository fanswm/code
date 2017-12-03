#!/usr/bin/python
# coding: utf-8
# Filename: backup_ver4.py
'''
This program for back_up.
'''

import os
import time

source = [ '/home/fanswm/log','/home/fanswm/bash' ]
target_dir = '/mnt/usb/backup/test'
today = target_dir + time.strftime('%Y%m%d')
now = time.strftime('%H%M%S')
commit = raw_input('Enter a commit -->')
if len(commit) == 0:
    target = today + os.sep + now + '.zip'
else:
    target = today + os.sep + now + '_' + \
        commit.replace(' ', '_') + '.zip'

if not os.path.exists(today):
    os.mkdir(today)
    print 'Successfully created directory', today

zip_command = 'zip -qr '%s' '%s' %(target,' '.join(source))

if os.system(zip_command) == 0:
    print 'Successfully backup to', target
else:
    print 'Backup failed'

if __name__ = '__main__':
    pass
