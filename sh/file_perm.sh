#!/bin/bash
# Program:
#   User input a filename, program will check th flowing:
#   1.) exist? 2.) file/directory? 3.) file permissions
#   This program shows "Hello World!" in your screen.
# History:
# 2016/04/09    fanswm  First release   from VBird
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin
export PATH

# 1. let user input name, input char is true?
echo -e "Please inputa filename, I will check the filename's type and\
             permission.\n\n"
read -p "Input a filename :" filename
test -z ${filename} && echo "You MUST input a filename." && exit 0

# 2. check filename is exist? NO: exit 0
test ! -e ${filename} && echo "The filename '${filename}' DO NOT exist" && exit 0

# 3. start check:
test -f ${filename} && filetype="regulare file"
test -d ${filename} && filetype="directory"
test -r ${filename} && perm="readable"
test -w ${filename} && perm="${perm} writeable"
test -x ${filename} && perm="${perm} executable"

# 4. start output info:
echo "The filename: ${filename} is a ${filetype}"
echo "And the permissions for you are : ${perm}"
exit 0
