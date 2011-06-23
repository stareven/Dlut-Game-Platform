#!/bin/bash
if [ -z $1 ];
then
echo "need project name"
exit
fi
name=$1
cd ${name}-build-desktop
#make -B Makefile
make
if [ $? -eq "0" ];
then
	echo finish build . start to run .
	echo
	./$name
fi
