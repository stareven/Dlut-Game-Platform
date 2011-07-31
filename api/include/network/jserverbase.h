#ifndef JSERVERBASE_H
#define JSERVERBASE_H

#include <QObject>

#include "serverapi_global.h"

class QTcpServer;
class QByteArray;
class QTcpSocket;
class JConnectionBase;

class SERVERAPISHARED_EXPORT JServerBase : public QObject
{
Q_OBJECT
public:
	explicit JServerBase(QObject *parent = 0);
    virtual quint16 run(quint16 port);
    quint16 serverPort()const;
protected:
	QTcpServer *m_server;
protected slots:
    void on_server_newConnection();
protected:
	virtual JConnectionBase* getConnection(QTcpSocket* socket,QObject* parent)const=0;
};

#endif // JSERVERBASE_H
