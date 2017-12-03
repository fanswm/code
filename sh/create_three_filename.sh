#!/bin/bash
# Program:
#   Program creates three files, which named by user's input and date command.
# History:
# 2016/04/10    fanswm  First release   from VBird
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin
export PATH

# 1. let user input filename, and get "fileuser" arugment;
echo -e "I will use 'touch' command to create 3 files."
read -p "Please input your filename: " fileuser

# 2. this filename is exist?
filename=${fileuser:-"fanswm"}

# 3. use date get filename:
date1=$(date --date='2 days ago' +%Y%m%d)
date2=$(date --date='1 days ago' +%Y%m%d)
date3=$(date +%Y%m%d)
file1=${filename}${date1}
file2=${filename}${date2}
file3=${filename}${date3}

# 4. create
touch "${file1}"
touch "${file2}"
touch "${file3}"
