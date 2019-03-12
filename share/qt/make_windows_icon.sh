#!/bin/bash
# create multiresolution windows icon
#mainnet
ICON_SRC=../../src/qt/res/icons/vhs.png
ICON_DST=../../src/qt/res/icons/vhs.ico
convert ${ICON_SRC} -resize 16x16 vhs-16.png
convert ${ICON_SRC} -resize 32x32 vhs-32.png
convert ${ICON_SRC} -resize 48x48 vhs-48.png
convert vhs-16.png vhs-32.png vhs-48.png ${ICON_DST}
#testnet
ICON_SRC=../../src/qt/res/icons/vhs_testnet.png
ICON_DST=../../src/qt/res/icons/vhs_testnet.ico
convert ${ICON_SRC} -resize 16x16 vhs-16.png
convert ${ICON_SRC} -resize 32x32 vhs-32.png
convert ${ICON_SRC} -resize 48x48 vhs-48.png
convert vhs-16.png vhs-32.png vhs-48.png ${ICON_DST}
rm vhs-16.png vhs-32.png vhs-48.png
