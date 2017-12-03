#!/bin/bash
#basedir=/backup/weekly
basedir=/home/fanswm/backup/weekly

PATH=/bin:/usr/bin:/sbin:/usr/sbin:
export PATH
export LANG=C

named=$basedir/named
postfixd=$basedir/postfix
sshd=$basedir/ssh
sambad=$basedir/samba
wwwd=$basedir/www
othters=$basedir/others
userinfod=$basedir/userinfo

for dirs in $named $postfixd $sshd $sambad $wwwd $others $userinfod
do
    [ ! -d "$dirs" ] && mkdir -p $dirs
done


cp -a /var/named/chroot/{etc,var}       $named
cp -a /etc/postfix /etc/dovecot.conf    $postfixd
cp -a /etc/ssh/*                        $sshd
cp -a /etc/samba/*                      $sambad
cp -a /etc{my.cnf,php.ini,httpd}        $wwwd
cd /var/lib
    tar -jpc -f $wwwd/mysql.tar.bz2     mysql
cd /var/www
    tar -jpc -f $wwwd/html.tar.bz2      html cgi-bin
cd /
    tar -jpc -f $others/etc.tar.bz2     etc
cd /usr
    tar -jpc -f $others/local.tar.bz2   local


cp -a /etc/{passwd,shadow,group}        $userinfod
cd $basedir/$userinfod
    chmod 700 ./*
cd /var/spool
    tar -jpc -f $userinfod/mail.tar.bz2 mail
#cd /
#    tar -jpc -f $userinfod/home.tar.bz2 home
cd /var/spool
    tar -jpc -f $userinfod/cron.tar.bz2 cron
