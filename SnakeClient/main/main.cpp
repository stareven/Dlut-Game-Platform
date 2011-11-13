#include <QtGui/QApplication>
#include "gui/mainwindow.h"

#include "service/jglobalsettings.h"
#include "network/jsnakesocket.h"

#include <DataStruct/SHost>
#include <DataStruct/JElapsedTimer>
#include <Helper/JConnectHelper>

void processArgument()
{
	QStringList arguments=QApplication::arguments();
	qDebug()<<arguments;
	JID userId=arguments.at(1).toInt();
	QString strcrypro=arguments.at(2);
	QByteArray crypro=QByteArray::fromHex(strcrypro.toAscii());
	GlobalSettings::g_userId = userId;
	GlobalSettings::g_loginhashcode = crypro;
	GlobalSettings::g_mainServer.m_address=arguments.at(3);
	GlobalSettings::g_mainServer.m_port=arguments.at(4).toInt();
	GlobalSettings::g_gameServer.m_address=arguments.at(5);
	GlobalSettings::g_gameServer.m_port=arguments.at(6).toInt();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	processArgument();
	JSnakeSocket *socket=JSnakeSocket::getInstance();
	JConnectHelper connectHelper(socket);
	connectHelper.connectToHost(GlobalSettings::g_gameServer);
	if(!connectHelper.waitForConnected(1000)){
		qDebug()<<"snake socket connect failed ."<<connectHelper.getConnectError();
		return 1;
	}
    MainWindow w;
    w.show();
    return a.exec();
}
