cd MainClient
if [ ! -f Makefile ];
then
qmake
fi
make
if [ $? -eq 0 ];
then
#cd ../MainClient-build-desktop
./MainClient
else
echo "make error ! can not run ."
read a
fi
