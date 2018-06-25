#!/bin/sh

echo "Continue?[Y/N]"
read -p "" yn
if [ ${yn} == "Y" ]; then
	echo "yes"
else
	yn="N"
	echo "Cancel 2 \n"
fi
