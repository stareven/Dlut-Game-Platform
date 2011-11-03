#include "jmainserver.h"

#include "jmainserversocket.h"
#include "jmainserverloginprocessor.h"
#include "jmainserverinformationprocessor.h"

JMainServer::JMainServer(QObject *parent) :
    JServerBase(parent)
{
}

JServerSocketBase* JMainServer::getConnection(QTcpSocket* socket,QObject* parent)const
{
	JServerSocketBase* connection = new JMainServerSocket(socket,parent);
	JServerNetworkDataProcessorBase* loginProcessor = new JMainServerLoginProcessor(connection);
	JServerNetworkDataProcessorBase* informationProcessor = new JMainServerInformationProcessor(connection);
	connection->registerProcessor(loginProcessor);
	connection->registerProcessor(informationProcessor);
	return connection;
}
