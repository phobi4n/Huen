#!/bin/bash

if [ $EUID == 0 ]; then
    echo "You need to run me as a regular user"
    exit 1
fi

if [ -f Makefile ]; then
    make distclean
fi

if [ -d $HOME/.local/share/huen ]; then
	rm -rfv $HOME/.local/share/huen
fi

if [ -x $HOME/.local/bin/Huen ]; then
	rm -v $HOME/.local/bin/Huen
fi

if [ -f $HOME/.local/share/applications/Huen.desktop ]; then
	rm -v $HOME/.local/share/applications/Huen.desktop
fi

if [ -d "$HOME/.local/share/plasma/desktoptheme/Huen" ]; then
	rm -rfv "$HOME/.local/share/plasma/desktoptheme/Huen"
fi
