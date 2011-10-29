#include "jmainserver.h"

#include "jmainserversocket.h"
#include "jmainserverloginprocessor.h"

JMainServer::JMainServer(QObject *parent) :
    JServerBase(parent)
{
}

JServerSocketBase* JMainServer::getConnection(QTcpSocket* socket,QObject* parent)const
{
	JServerSocketBase* connection = new JMainServerSocket(socket,parent);
	JServerNetworkDataProcessorBase* loginProcessor = new JMainServerLoginProcessor(connection);
	connection->registerProcessor(loginProcessor);
	return connection;
}
