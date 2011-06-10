#include <QtCore/QCoreApplication>
#include <QDebug>

#include "network/jserverbase.h"
#include "service/jportservice.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JServerBase loginServer(EST_LOGIN);
    qDebug()<<"Login Server : port is "<<loginServer.run(37376);
    JServerBase gameInfoServer(EST_GAMEINFO);
    qDebug()<<"gameInfo Server : port is "<<gameInfoServer.run(37375);
    JServerBase secretportServer(EST_SECRETPORT);
    qDebug()<<"secretport Server : port is "<<secretportServer.run(37374);
    JServerBase freeportServer(EST_FREEPORT);
    qDebug()<<"freeport Server : port is "<<freeportServer.run(37373);
	JServerBase subserverServer(EST_SUBSERVER);
	qDebug()<<"subserver Server : port is "<<subserverServer.run (0);
    JPortService freeps(JPortService::EPS_FREE);
    freeps.addSubServerPort(loginServer);
    freeps.addSubServerPort(secretportServer);
    JPortService secretps(JPortService::EPS_SECRET);
    secretps.addSubServerPort(gameInfoServer);
	secretps.addSubServerPort (subserverServer);
    return a.exec();
}
