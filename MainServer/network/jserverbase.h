#ifndef JSERVERBASE_H
#define JSERVERBASE_H

#include <QObject>

#include "jconnectionfactory.h"

class QTcpServer;
class QByteArray;
class QTcpSocket;
class JConnectionBase;

class JServerBase : public QObject
{
Q_OBJECT
public:
    explicit JServerBase(EServerType,QObject *parent = 0);
    virtual quint16 run(quint16 port);
    quint16 serverPort()const;
    EServerType serverType()const;

protected:
    QTcpServer *m_server;
    const EServerType m_servertype;
protected slots:
    void on_server_newConnection();
};

#endif // JSERVERBASE_H
