#include "jsnakeserver.h"

#include "jsnakeconnection.h"

JSnakeServer::JSnakeServer(QObject *parent) :
    JServerBase(parent)
{
}

JConnectionBase* JSnakeServer::getConnection(QTcpSocket* socket,QObject* parent)const
{
	return new JSnakeConnection(socket,parent);
}
