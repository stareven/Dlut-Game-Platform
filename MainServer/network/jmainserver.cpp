#include "jmainserver.h"

#include <Socket/JSession>

#include "jmainserversocket.h"
#include "jmainserverloginprocessor.h"
#include "jmainserverinformationprocessor.h"
#include "jmainservercommandprocessor.h"

JMainServer::JMainServer(QObject *parent) :
    JServerBase(parent)
{
}

JServerSocketBase* JMainServer::getConnection(QTcpSocket* socket,QObject* parent)const
{
	JMainServerSocket* connection = new JMainServerSocket(socket,parent);
	JServerNetworkDataProcessorBase* loginProcessor = new JMainServerLoginProcessor(connection);
	JServerNetworkDataProcessorBase* informationProcessor = new JMainServerInformationProcessor(connection);
	JServerNetworkDataProcessorBase* commandProcessor = new JMainServerCommandProcessor(connection);
	connection->registerProcessor(loginProcessor);
	connection->registerProcessor(informationProcessor);
	connection->registerProcessor(commandProcessor);
	return connection;
}
