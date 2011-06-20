#ifndef JSERVERTYPE_H
#define JSERVERTYPE_H

#include <QObject>

#include "global/eportsrv.h"

class QTcpServer;
class QByteArray;
class QTcpSocket;
class JConnectionBase;

class JServerType : public QObject
{
Q_OBJECT
public:
    explicit JServerType(EServerType,QObject *parent = 0);
    virtual quint16 run(quint16 port);
    quint16 serverPort()const;
    EServerType serverType()const;

protected:
    QTcpServer *m_server;
    const EServerType m_servertype;
protected slots:
    void on_server_newConnection();
};

#endif // JSERVERTYPE_H
