#include "jpseudoserver.h"

#include "jpseudoserversocket.h"
#include "jpseudoserverinformationprocessor.h"

JPseudoServer::JPseudoServer(QObject *parent) :
    JServerBase(parent)
{
}

JServerSocketBase* JPseudoServer::getConnection(QTcpSocket* socket,QObject* parent)const
{
	JPseudoServerSocket* connection = new JPseudoServerSocket(socket,parent);
	JServerNetworkDataProcessorBase* informationProcessor = new JPseudoServerInformationProcessor(connection);
	connection->registerProcessor(informationProcessor);
	return connection;
}
