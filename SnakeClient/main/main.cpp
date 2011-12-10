#include <QtGui/QApplication>
#include "gui/mainwindow.h"

#include "network/jsnakesocket.h"

#include <DataStruct/SHost>
#include <DataStruct/JElapsedTimer>
#include <Helper/JConnectHelper>
#include <Helper/JGameClientArgumentAnalyser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JGameClientArgumentAnalyser *gcaa = JGameClientArgumentAnalyser::getInstance();
    gcaa->processArgument(a.arguments());
	JSnakeSocket *socket=JSnakeSocket::getInstance();
	JConnectHelper connectHelper(socket);
    connectHelper.connectToHost(gcaa->getGameServer());
	if(!connectHelper.waitForConnected(1000)){
		qDebug()<<"snake socket connect failed ."<<connectHelper.getConnectError();
		return 1;
	}
    MainWindow w;
    w.show();
    return a.exec();
}
