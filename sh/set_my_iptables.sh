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

#打开POP3服务端口的tcp协议 
#iptables -A INPUT -p tcp --dport 110 -j ACCEPT 

#打开SMTP服务端口的tcp协议 
iptables -A INPUT -p tcp --dport 25 -j ACCEPT 

#打开FTP服务端口的tcp协议 
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


#允许DNS服务端口的tcp数据包流入 
iptables -A INPUT -p tcp --dport 53 -j ACCEPT 

#允许DNS服务端口的udp数据包流入 
iptables -A INPUT -p udp --dport 53 -j ACCEPT 

#iptables -A INPUT -p icmp -icmp-type echo-request -i eth1 -j DROP 
#防止死亡之ping，从接口eth1进入的icmp协议的请求全部丢弃。 

#防止SYN Flood (拒绝服务攻击)
iptables -A FORWARD -p tcp --syn -m limit --limit 1/s -j ACCEPT 

#iptables -t nat -A POSTROUTING -o eth1 -s 192.168.0.226 -j MASQUERADE
#允许 192.168.0.226通过eth1 IP伪装出外网
#iptables -t nat -A POSTROUTING -o eth0 -s 192.168.0.4 -p tcp --dport 25 -j MASQUERADE
#允许 192.168.0.4通过eth0 伪装访问外网的 25端口
