#!/bin/bash
#coding: utf-8

sudo apt-get install preload
#后台的守护进程，加速应用载入时间

#减少过热
sudo add-apt-repository ppa:linrunner/tlp
sudo apt-get update
sudo apt-get install tlp tlp-rdw
sudo tlp start

#安装 CPUFREQ 指示器：
sudo apt-get install indicator-cpufreq
#重启你的电脑并使用 Powersave 模式
