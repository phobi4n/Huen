#!/bin/bash

if [ $EUID != 0 ]; then
    echo "You need to run me as sudo"
    exit 1
fi

if [ -f Makefile ]; then
    make distclean
fi

qmake
make

if [ -x Huen ]; then
    mkdir -pv /usr/share/huen
    cp -rv ./usertheme/* /usr/share/huen
    cp -v ./Huen /usr/bin
    cp -v ./huen-icon.svg /usr/share/icons/hicolor/scalable/apps
    cp -v ./Huen.desktop /usr/share/applications
else
    echo ""
    echo "Compiling the binary failed. Check Qt-Dev and ImageMagick-Dev packages are installed."
fi
