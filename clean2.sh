#!/bin/bash -e
paths=`ls | grep "\-build\-desktop"`
for path in $paths
do
cd $path
make clean
cd ..
done
echo "press any key to exit"
read -N 1
