#include "jgfsserver.h"

#include "jgfsconnection.h"

JGfsServer::JGfsServer(QObject *parent) :
    JServerBase(parent)
{
}

JConnectionBase* JGfsServer::getConnection(QTcpSocket* socket,QObject* parent)const
{
	return new JGfsConnection(socket,parent);
}
