#!/bin/bash

for pro in `find . -name '*.pro'`
do
	echo $pro
	bd=`dirname $pro`/../`basename $pro | sed 's#\.pro##'`-build-desktop
	echo $bd
	qmake $pro -o $bd/Makefile
	make -C $bd
done
