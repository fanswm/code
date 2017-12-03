#!/bin/bash
# Program:
#   useradd many account;
# History:
# 2016/04/12    fanswm  First release   from VBird
PATH=/bin:/sbin:/usr/bin:/usr/sbin
export PATH

# check account.txt is not exist?
if [ ! -f account.txt ]; then
    echo "requiet 'account.txt' is not exist! Please create it: one account one row."
    exit 1
fi

usernames = $ (cat account.txt)

for username in $usernames
do
    useradd $username
    echo $username | passwd --stdin $username
    chage -d 0 $username
done
