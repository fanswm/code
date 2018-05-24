#!/bin/bash
# coding: utf-8

echo "1. Now, Install chrome..."
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo dpkg -i *.deb

echo "2. Now, Uninstall amazon..."
sudo apt-get remove unity-webapps-common

echo "3. Now, Install Gdebi..."
sudo apt-get install gdebi

echo "4. Now, Install Git..."
sudo atp-get install git

echo "5. Now, Install vim..."
sudo apt-get install vim

echo "6. Now, Install Curl and tsocks, jq..."
sudo apt-get install curl tsocks jq

echo "Basic is completed."

### 
echo "7. Now, Install SSR..."
sudo apt-get install build-essential
wget https://github.com/jedisct1/libsodium/releases/download/1.0.16/libsodium-1.0.16.tar.gz
tar zxvf ./libsodium-1.0.16
cd ./libsodium-1.0.16
./configure && make -j3 &&sudo make install
sudo ldconfig
cd ~
cp ~/github/code/sh/ssr.sh /usr/local/bin/
sudo chmod u+x /usr/local/bin/ssr.sh

ssr install
ssr update
# or: ## ssr config #tian ru your config
ssr start

echo "8. Now, Install proxychains..."
sudo apt-get install proxychains
echo "config it..."
echo "COMMAND: sudo vim /etc/proxychains.conf"
echo "change: under [ProxyList]:"
echo "socks5 127.0.0.1 1080"
sudo vim /etc/proxychains.conf
echo "8 done."

echo "9. Now, Install Gnome-tweak_tool"
sudo apt-get install gnome-tweak-tool

#echo "icons use papirus..."
#sudo add-apt-repository ppa:papirus/papirus
#sudo apt update
#sudo apt-get install papirus-icon-theme

echo "10. Now, Install ocs-url..."
wget https://www.linux-apps.com/p/1136805/startdownload?file_id=1517920714&file_name=ocs-url_3.0.3-0ubuntu1_amd64.deb&file_type=application/x-debian-package&file_size=54198&url=https%3A%2F%2Fdl.opendesktop.org%2Fapi%2Ffiles%2Fdownloadfile%2Fid%2F1517920714%2Fs%2F95a8a998d7917cbf5d33ba03ceaa334b%2Ft%2F1523007214%2Fu%2F71764%2Focs-url_3.0.3-0ubuntu1_amd64.deb
sudo dpkg -i ocs-url_3.0.3-0ubuntu1_amd64.deb
echo "10 done"

echo "11. Now, Install flat-remix-gnome-theme..."
#cd /tmp && rm -rf flat-remix-gnome-theme && \
#git clone https://github.com/daniruiz/flat-remix-gnome && \
#mkdir -p ~/.themes && cp -r /tmp/flat-remix-gnome/Flat-Remix* ~/.themes && \
#gsettings set org.gnome.shell.extensions.user-theme name "Flat-Remix";
sudo add-apt-repository ppa:daniruiz/flat-remix
sudo apt-get update
sudo apt-get install flat-remix-gnome
echo "11 done."

echo "12. Now Install guake..."
sudo apt-get install guake
echo "12 done.\n"

echo "13. Now, Install zsh..."
sudo apt-get install zsh
#安装oh-my-zsh
wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | sh
echo "edit .zshrc"

echo "14. Now, Install albert..."
sudo add-apt-repository ppa:noobslab/macbuntu
sudo apt-get update
sudo apt-get install albert
echo "14 done.\n"


echo "15. Now, Install Dash-to-dock..."
cp -R ~/Downloads/dash-to-dock@micxgx.gmail.com/ ~/.local/share/gnome-shell/extension/
echo "emmmmm... restart gnome(Alt+F2: r) and reset gnome-tweak"
echo "15 done.\n"
