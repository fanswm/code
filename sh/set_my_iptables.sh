#!/bin/bash
# Filename: iptables config

# default drop rules: drop all first, append new rules witch require 
iptables -P INPUT DROP
#iptables -P FORWARD DROP

# web->tcp
iptables -A INPUT -p tcp --dport 80 -j ACCEPT 
iptables -A INPUT -p tcp --dport 18080 -j ACCEPT

# samba 
iptables -A INPUT -p tcp --dport 139 -j ACCEPT 
iptables -A INPUT -p udp --dport 137 -j ACCEPT 

# openvpn
iptables -A INPUT -p tcp --dport 1194 -j ACCEPT 

# syncthing
iptables -A INPUT -p tcp --dport 8384 -j ACCEPT 

# leanote
iptables -A INPUT -p tcp --dport 9001 -j ACCEPT 

#��POP3����˿ڵ�tcpЭ�� 
#iptables -A INPUT -p tcp --dport 110 -j ACCEPT 

#��SMTP����˿ڵ�tcpЭ�� 
iptables -A INPUT -p tcp --dport 25 -j ACCEPT 

#��FTP����˿ڵ�tcpЭ�� 
#iptables -A INPUT -p tcp --dport 21 -j ACCEPT 

# ssh white list:
# win10 IP:
iptables -A INPUT -p tcp -s 192.168.31.113 --dport 22 -j ACCEPT
# PI IP: 
iptables -A INPUT -p tcp -s abpage.freedynamicdns.org --dport 22 -j ACCEPT
# jhk public IP:
iptables -A INPUT -p tcp -s 222.223.232.82 --dport 22 -j ACCEPT 
# jhk:
iptables -A INPUT -p tcp -m mac --mac-source 94:DE:80:44:85:2D --dport 22 -j ACCEPT
# win10:
iptables -A INPUT -p tcp -m mac --mac-source 90:fb:a6:3d:12:21 --dport 22 -j ACCEPT
# android:
iptables -A INPUT -p tcp -m mac --mac-source 60:d9:a0:f0:ee:b4 --dport 22 -j ACCEPT
# pi:
iptables -A INPUT -p tcp -m mac --mac-source b8:27:eb:5a:e7:70 --dport 22 -j ACCEPT


#����DNS����˿ڵ�tcp���ݰ����� 
iptables -A INPUT -p tcp --dport 53 -j ACCEPT 

#����DNS����˿ڵ�udp���ݰ����� 
iptables -A INPUT -p udp --dport 53 -j ACCEPT 

#iptables -A INPUT -p icmp -icmp-type echo-request -i eth1 -j DROP 
#��ֹ����֮ping���ӽӿ�eth1�����icmpЭ�������ȫ�������� 

#��ֹSYN Flood (�ܾ����񹥻�)
iptables -A FORWARD -p tcp --syn -m limit --limit 1/s -j ACCEPT 

#iptables -t nat -A POSTROUTING -o eth1 -s 192.168.0.226 -j MASQUERADE
#���� 192.168.0.226ͨ��eth1 IPαװ������
#iptables -t nat -A POSTROUTING -o eth0 -s 192.168.0.4 -p tcp --dport 25 -j MASQUERADE
#���� 192.168.0.4ͨ��eth0 αװ���������� 25�˿�
