#!/bin/bash -e
paths=`ls | grep "\-build\-desktop"`
for path in $paths
do
cd $path
make
cd ..
done
echo "press enter key to exit"
read a
