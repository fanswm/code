#!/bin/bash
# coding: utf-8

## 1
echo "1. Now, Install chrome..."
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
	sudo dpkg -i *.deb
	echo -e "1 done.\n"
	yn="N"
else
	echo -e "Cancel 1 \n"
fi

## 2
echo "2. Now, Uninstall amazon..."
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	sudo apt-get remove unity-webapps-common
	echo -e "2 done.\n"
	yn="N"
else
	echo -e "Cancel 2 \n"
fi

## 3
echo "3. Now, Install Gdebi..."
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	sudo apt-get install gdebi
	echo -e "3 done.\n"
	yn="N"
else
	echo -e "Cancel 3 \n"
fi

## 4
echo "4. Now, Install Git..."
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	sudo atp-get install git
	echo -e "4 done.\n"
	yn="N"
else
	echo -e "Cancel 4 \n"
fi

## 5
echo "5. Now, Install vim..."
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	sudo apt-get install vim
	echo -e "5 done.\n"
	yn="N"
else
	echo -e "Cancel 5 \n"
fi

## 6
echo "6. Now, Install Curl and tsocks, jq..."
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	sudo apt-get install curl tsocks jq
	echo -e "6 done.\n"
	yn="N"
else
	echo -e "Cancel 6 \n"
fi

echo "Basic is completed."

## 7
echo "7. Now, Install SSR..."
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
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
	echo -e "7 done.\n"
	yn="N"
else
	echo -e "Cancel 7 \n"
fi

## 8
echo "8. Now, Install proxychains..."
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	sudo apt-get install proxychains
	echo "config it..."
	echo "COMMAND: sudo vim /etc/proxychains.conf"
	echo "change: under [ProxyList]:"
	echo "socks5 127.0.0.1 1080"
	sudo vim /etc/proxychains.conf
	echo "8 done."
	yn="N"
else
	echo -e "Cancel 8 \n"
fi

## 9
echo "9. Now, Install Gnome-tweak_tool"
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	sudo apt-get install gnome-tweak-tool
	echo -e "9 done.\n"
	yn="N"
else
	echo -e "Cancel 9 \n"
fi

#echo "icons use papirus..."
#sudo add-apt-repository ppa:papirus/papirus
#sudo apt update
#sudo apt-get install papirus-icon-theme

## 10
echo "10. Now, Install ocs-url..."
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	wget https://www.linux-apps.com/p/1136805/startdownload?file_id=1517920714&file_name=ocs-url_3.0.3-0ubuntu1_amd64.deb&file_type=application/x-debian-package&file_size=54198&url=https%3A%2F%2Fdl.opendesktop.org%2Fapi%2Ffiles%2Fdownloadfile%2Fid%2F1517920714%2Fs%2F95a8a998d7917cbf5d33ba03ceaa334b%2Ft%2F1523007214%2Fu%2F71764%2Focs-url_3.0.3-0ubuntu1_amd64.deb
	sudo dpkg -i ocs-url_3.0.3-0ubuntu1_amd64.deb
	echo "10 done"
	yn="N"
else
	echo -e "Cancel 10 \n"
fi

## 11
echo "11. Now, Install flat-remix-gnome-theme..."
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	#cd /tmp && rm -rf flat-remix-gnome-theme && \
	#git clone https://github.com/daniruiz/flat-remix-gnome && \
	#mkdir -p ~/.themes && cp -r /tmp/flat-remix-gnome/Flat-Remix* ~/.themes && \
	#gsettings set org.gnome.shell.extensions.user-theme name "Flat-Remix";
	sudo add-apt-repository ppa:daniruiz/flat-remix
	sudo apt-get update
	sudo apt-get install flat-remix-gnome
	echo "11 done."
	yn="N"
else
	echo -e "Cancel 11 \n"
fi

## 12
echo "12. Now Install guake..."
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	sudo apt-get install guake
	echo -e "12 done.\n"
	yn="N"
else
	echo -e "Cancel 12 \n"
fi

## 13
echo "13. Now, Install zsh..."
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	sudo apt-get install zsh
	# install oh-my-zsh
	wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | sh
	echo "edit .zshrc"
	vim ./.zshrc
	yn="N"
	echo "13 done."
else
	echo -e "Cancel 2 \n"
fi

## 14
echo "14. Now, Install albert..."
<<<<<<< HEAD
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	sudo add-apt-repository ppa:noobslab/macbuntu
	sudo apt-get update
	sudo apt-get install albert
	echo -e "14 done.\n"
	yn="N"
else
	echo -e "Cancel 14 \n"
fi

## 15
echo "15. Now, Install Dash-to-dock..."
echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	cp -R ~/Downloads/dash-to-dock@micxgx.gmail.com/ ~/.local/share/gnome-shell/extension/
	echo "emmmmm... restart gnome(Alt+F2: r) and reset gnome-tweak"
	echo -e "15 done.\n"
	yn="N"
else
	echo -e "Cancel 15 \n"
fi

## echo "ALL completed! Bye!"
=======
sudo add-apt-repository ppa:noobslab/macbuntu
sudo apt-get update
sudo apt-get install albert
echo "14 done.\n"


echo "15. Now, Install Dash-to-dock..."
cp -R ~/Downloads/dash-to-dock@micxgx.gmail.com/ ~/.local/share/gnome-shell/extension/
echo "emmmmm... restart gnome(Alt+F2: r) and reset gnome-tweak"
echo "15 done.\n"
>>>>>>> e8cb1037be423c529fc8e34c825a722503a2cb7c