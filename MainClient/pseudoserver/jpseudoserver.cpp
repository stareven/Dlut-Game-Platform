#include "jpseudoserver.h"

#include <QCoreApplication>

#include <Session/JSession>

#include "jpseudoserversocket.h"
#include "jpseudoserverinformationprocessor.h"

JPseudoServer::JPseudoServer(QObject *parent) :
    JServerBase(parent)
{
}

JPseudoServer* JPseudoServer::getInstance()
{
	static JPseudoServer* instance = NULL;
	if(NULL == instance){
		instance = new JPseudoServer(QCoreApplication::instance());
		instance->run(50373);
	}
	return instance;
}

JServerSocketBase* JPseudoServer::getConnection(QTcpSocket* socket,QObject* parent)const
{
	JPseudoServerSocket* connection = new JPseudoServerSocket(socket,parent);
	JSession* session = new JSession(connection);
	JServerNetworkDataProcessorBase* informationProcessor = new JPseudoServerInformationProcessor(session,connection);
	connection->registerProcessor(informationProcessor);
	return connection;
}
