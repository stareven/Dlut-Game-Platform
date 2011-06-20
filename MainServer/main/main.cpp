#include <QtCore/QCoreApplication>
#include <QDebug>

#include "network/jservertype.h"
#include "service/jportmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JServerType loginServer(EST_LOGIN);
    qDebug()<<"Login Server : port is "<<loginServer.run(37376);
    JServerType gameInfoServer(EST_GAMEINFO);
    qDebug()<<"gameInfo Server : port is "<<gameInfoServer.run(37375);
    JServerType secretportServer(EST_SECRETPORT);
    qDebug()<<"secretport Server : port is "<<secretportServer.run(37374);
    JServerType freeportServer(EST_FREEPORT);
    qDebug()<<"freeport Server : port is "<<freeportServer.run(37373);
	JServerType subserverServer(EST_SUBSERVER);
	qDebug()<<"subserver Server : port is "<<subserverServer.run (0);
    JPortManager freeps(JPortManager::EPS_FREE);
    freeps.addSubServerPort(loginServer);
    freeps.addSubServerPort(secretportServer);
    JPortManager secretps(JPortManager::EPS_SECRET);
    secretps.addSubServerPort(gameInfoServer);
	secretps.addSubServerPort (subserverServer);
    return a.exec();
}
