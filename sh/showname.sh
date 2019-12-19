#!/bin/bash
# Program:
#   User inputs his first name and last name.Program shows his full name.
# History:
# 2016/04/10    fanswm  First release   from VBird
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin
export PATH

read -p "Please input your first name:" firstname
read -p "Please input your last name:" lastname
echo -e "\nYour full name is : ${firstname} ${lastname}"
