#ifndef JCONNECTIONFACTORY_H
#define JCONNECTIONFACTORY_H

#include "global/eportsrv.h"

class JConnectionBase;
class QTcpSocket;
class QObject;

class JConnectionFactory
{
public:
    JConnectionFactory();
//    enum EServerType{EST_LOGIN,EST_GAMEINFO,EST_FREEPORT,EST_SECRETPORT,EST_MAX};
    JConnectionBase* createConnection(EServerType,QTcpSocket* socket,QObject* parent);
};

#endif // JCONNECTIONFACTORY_H
