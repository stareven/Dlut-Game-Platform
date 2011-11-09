#include "jpseudoserver.h"

#include <Session/JSession>

#include "jpseudoserversocket.h"
#include "jpseudoserverinformationprocessor.h"

JPseudoServer::JPseudoServer(QObject *parent) :
    JServerBase(parent)
{
}

JServerSocketBase* JPseudoServer::getConnection(QTcpSocket* socket,QObject* parent)const
{
	JPseudoServerSocket* connection = new JPseudoServerSocket(socket,parent);
	JSession* session = new JSession(connection);
	JServerNetworkDataProcessorBase* informationProcessor = new JPseudoServerInformationProcessor(session,connection);
	connection->registerProcessor(informationProcessor);
	return connection;
}
