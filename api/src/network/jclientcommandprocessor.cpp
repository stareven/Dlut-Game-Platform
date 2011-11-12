#include "jclientcommandprocessor.h"

#include "jclientsocketbase.h"
#include "jsession.h"

JClientCommandProcessor::JClientCommandProcessor(JSession* session,JSocketBase *socket) :
	JClientNetworkDataProcessorBase(session,socket)
{
}

JClientCommandProcessor* JClientCommandProcessor::getInstance()
{
	static JClientCommandProcessor* instance=NULL;
	if(NULL==instance){
		JClientSocketBase* socket=JClientSocketBase::getInstance();
		JSession* session = socket->getSession();
		instance = new JClientCommandProcessor(session,socket);
		socket->registerProcessor(instance);
	}
	return instance;
}

void JClientCommandProcessor::sendCommand(ECommandType type,JID param1)
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<(JID)type;
	stream<<param1;
	sendData(data);
}

void JClientCommandProcessor::process(const QByteArray&)
{
	qDebug()<<"JClientCommandProcessor::process . There should not be any responce.";
}

EProcessorType JClientCommandProcessor::getProcessorType()const
{
	return EPI_COMMAND;
}
