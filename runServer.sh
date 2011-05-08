cd MainServer
if [ ! -f Makefile ];
then
qmake
fi
make
#cd ../MainServer-build-desktop
./MainServer
