
Debian
====================
This directory contains files used to package vhsd/vhs-qt
for Debian-based Linux systems. If you compile vhsd/vhs-qt yourself, there are some useful files here.

## vhs: URI support ##


vhs-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install vhs-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your vhsqt binary to `/usr/bin`
and the `../../share/pixmaps/vhs128.png` to `/usr/share/pixmaps`

vhs-qt.protocol (KDE)
