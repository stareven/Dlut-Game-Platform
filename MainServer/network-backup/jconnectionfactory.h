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
    JConnectionBase* createConnection(EServerType,QTcpSocket* socket,QObject* parent);
};

#endif // JCONNECTIONFACTORY_H
