#ifndef JSERVERTYPE_H
#define JSERVERTYPE_H

#include <QObject>

#include "global/eportsrv.h"
#include "network/jserverbase.h"

class JServerType : public JServerBase
{
Q_OBJECT
public:
    explicit JServerType(EServerType,QObject *parent = 0);
//    virtual quint16 run(quint16 port);
//    quint16 serverPort()const;
    EServerType serverType()const;

protected:
//    QTcpServer *m_server;
	const EServerType m_servertype;
//protected slots:
//    void on_server_newConnection();
protected:
	JConnectionBase* getConnection(QTcpSocket* socket,QObject* parent)const;
};

#endif // JSERVERTYPE_H
