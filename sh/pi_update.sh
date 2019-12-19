#!/bin/bash
# Program:
#  This pi will be update && upgrade 
# History:
# 2016/10/14    fanswm  First release
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin
export PATH

echo -e "\nYour will update and upgrade... "
sudo apt-get update && apt-get upgrade -y &
echo -e "\nThe update is ready!\n"
