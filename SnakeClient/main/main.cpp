#include <QtGui/QApplication>
#include "gui/mainwindow.h"

#include "service/jglobalsettings.h"

void processArgument()
{
	QStringList arguments=QApplication::arguments();
	qDebug()<<arguments;
	GlobalSettings::g_userId=arguments.at(1).toInt();
	QString crypro=arguments.at(2);
	qDebug()<<crypro;
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
