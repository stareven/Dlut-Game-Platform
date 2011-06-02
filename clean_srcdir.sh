#!/bin/bash
clean()
{
	rm -fv *.o
	rm -fv moc_*.cpp
	rm -fv ui_*.h
	rm -fv *.user
	rm -fv Makefile
	rm -fv *.so*
	rm -fv qrc_*.cpp
	rm -fv `pwd | awk -F '/' '{printf $NF "\n" }' `
}
basepath=`pwd`
cd ${basepath}/MainClient
echo "${basepath}/MainClient"
clean
cd ${basepath}/MainServer
echo "${basepath}/MainServer"
clean
echo "press any key to exit"
read -N 1
