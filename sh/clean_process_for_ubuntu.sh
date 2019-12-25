#!/bin/bash
# coding: utf-8

# accounts-daemon.service
sudo systemctl stop accounts-daemon.service
sudo systemctl disable accounts-daemon.service
sudo systemctl mask accounts-daemon.service

# avahi-daemon.service
sudo systemctl stop avahi-daemon.service
sudo systemctl disable avahi-daemon.service
sudo systemctl mask avahi-daemon.service

# bluetooth.service
sudo systemctl stop bluetooth.service
sudo systemctl disable bluetooth.service
sudo systemctl mask bluetooth.service

# ModemManager.service
sudo systemctl stop ModemManager.service
sudo systemctl disable ModemManager.service
sudo systemctl mask ModemManager.service

# pppd-dns.service
sudo systemctl stop pppd-dns.service
sudo systemctl disable pppd-dns.service
sudo systemctl mask pppd-dns.service

# whoopsie.service
sudo systemctl stop whoopsie.service
sudo systemctl disable whoopsie.service
sudo systemctl mask whoopsie.service

