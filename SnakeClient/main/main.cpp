#include <QtGui/QApplication>
#include "gui/mainwindow.h"

#include "service/jglobalsettings.h"
#include "service/jcryprorecorder.h"

void processArgument()
{
	QStringList arguments=QApplication::arguments();
	qDebug()<<arguments;
	JID userId=arguments.at(1).toInt();
	QString strcrypro=arguments.at(2);
	QByteArray crypro=QByteArray::fromHex(strcrypro.toAscii());
	JCryproRecorder cr;
	cr.set(crypro,userId);
	GlobalSettings::g_mainServer.m_address=arguments.at(3);
	GlobalSettings::g_mainServer.m_port=arguments.at(4).toInt();
	GlobalSettings::g_gameServer.m_address=arguments.at(5);
	GlobalSettings::g_gameServer.m_port=arguments.at(6).toInt();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	processArgument();
    MainWindow w;
    w.show();
    return a.exec();
}
