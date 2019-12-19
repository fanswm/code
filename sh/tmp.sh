<<<<<<< HEAD
#!/bin/sh

echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	echo "yes"
else
	yn="N"
	echo "Cancel 2 \n"
fi
=======
cd ~/.local/share/gnome-shell/extensions/
git clone https://github.com/mlutfy/hidetopbar.git hidetopbar@mathieu.bidon.ca
cd hidetopbar@mathieu.bidon.ca
make schemas
gnome-shell-extension-tool -e hidetopbar@mathieu.bidon.ca
gnome-shell --replace &
>>>>>>> 467a1da9e8e583e2dac3869a6da2cb650f18a595
