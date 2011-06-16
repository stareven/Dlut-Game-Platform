#include <QtCore/QCoreApplication>

#include <QDebug>

#include "network/jserverbase.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	JServerBase server;
	qDebug()<<"GameFileServer1 startup :"<<server.run(50123);
    return a.exec();
}
