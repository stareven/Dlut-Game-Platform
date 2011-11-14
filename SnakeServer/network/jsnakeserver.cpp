#include "jsnakeserver.h"

#include "jsnakeserversocket.h"
#include "jsnakeserverprocessor.h"

JSnakeServer::JSnakeServer(QObject *parent) :
    JServerBase(parent)
{
}

JServerSocketBase* JSnakeServer::getConnection(QTcpSocket* socket,QObject* parent)const
{
	JSnakeServerSocket* connection = new JSnakeServerSocket(socket,parent);
	JSession* session = connection->getSession();
	JServerNetworkDataProcessorBase* snakeProcessor = new JSnakeServerProcessor(session,connection);
	connection->registerProcessor(snakeProcessor);
	return connection;
}
