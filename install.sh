#!/bin/bash

if [ $EUID == 0 ]; then
    echo "You need to run me as a regular user."
    exit 1
fi

#USER_HOME=$(eval echo ~$SUDO_USER)
#echo $USER_HOME

if [ -f Makefile ]; then
    make distclean
fi

qmake
make -j2

if [ -x Huen ]; then

	if [ -d "$HOME/.local/share/plasma/desktoptheme/Huen" ]; then
		echo "LOCAL COPY EXISTS. Deleting."
		rm -rf "$HOME/.local/share/plasma/desktoptheme/Huen"
	fi

    mkdir -pv $HOME/.local/share/huen
    cp -rfv ./usertheme/* $HOME/.local/share/huen
    cp -fv ./Huen $HOME/.local/bin
    cp -fv ./huen-icon.svg $HOME/.local/share/icons/hicolor/scalable/apps
    cp -fv ./Huen.desktop  $HOME/.local/share/applications
else
    echo ""
    echo "Compiling the binary failed. Check Qt-Dev and ImageMagick-Dev packages are installed."
fi
