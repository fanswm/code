#!/bin/bash
# Program:
# This program will show string:"it's time for having a rest! please!" in your screen.
# History:
# 2016/09/13 fanswm First released
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

if [ -f ~/.bash_profile ];
then
    .~/.bash_profile
fi

/bin/echo -e "It's time for having a rest! Please! \a \n"
/bin/cat /home/fanswm/sh/have_rest.bash
#exit 0
