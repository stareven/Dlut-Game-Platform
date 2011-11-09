#include "jmainserver.h"

#include "jmainserversocket.h"
#include "jmainserverloginprocessor.h"
#include "jmainserverinformationprocessor.h"
#include "jmainservercommandprocessor.h"
#include "jmainserversession.h"

JMainServer::JMainServer(QObject *parent) :
    JServerBase(parent)
{
}

JServerSocketBase* JMainServer::getConnection(QTcpSocket* socket,QObject* parent)const
{
	JMainServerSocket* connection = new JMainServerSocket(socket,parent);
	JMainServerSession* session = new JMainServerSession(connection);
	JServerNetworkDataProcessorBase* loginProcessor = new JMainServerLoginProcessor(session,connection);
	JServerNetworkDataProcessorBase* informationProcessor = new JMainServerInformationProcessor(session,connection);
	JServerNetworkDataProcessorBase* commandProcessor = new JMainServerCommandProcessor(session,connection);
	connection->registerProcessor(loginProcessor);
	connection->registerProcessor(informationProcessor);
	connection->registerProcessor(commandProcessor);
	return connection;
}
