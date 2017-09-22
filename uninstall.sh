#!/bin/bash

if [ $EUID != 0 ]; then
    echo "You need to run me as sudo"
    exit 1
fi

if [ -f Makefile ]; then
    make distclean
fi

if [ -d /usr/share/huen ]; then
	rm -rv /usr/share/huen
fi

if [ -x /usr/bin/Huen ]; then
	rm -v /usr/bin/Huen
fi

if [ -f /usr/share/applications/Huen.desktop ]; then
	rm -v /usr/share/applications/Huen.desktop
fi

if [ -d "$USER_HOME/.local/share/plasma/desktoptheme/Huen" ]; then
	rm -rf "$USER_HOME/.local/share/plasma/desktoptheme/Huen"
fi
