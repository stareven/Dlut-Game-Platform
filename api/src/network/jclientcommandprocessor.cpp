#include "jclientcommandprocessor.h"

#include "jclientsocketbase.h"

JClientCommandProcessor::JClientCommandProcessor(JClientSocketBase *socket) :
	JClientNetworkDataProcessorBase(socket)
{
}

JClientCommandProcessor* JClientCommandProcessor::getInstance()
{
	static JClientCommandProcessor* instance=NULL;
	if(NULL==instance){
		JClientSocketBase* socket=JClientSocketBase::getInstance();
		instance = new JClientCommandProcessor(socket);
		socket->registerProcessor(instance);
	}
	return instance;
}

void JClientCommandProcessor::sendCommand(JClientCommandProcessor::ECommandType type,JID param1)
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<type;
	stream<<param1;
	sendData(data);
}

void JClientCommandProcessor::process(const QByteArray&)
{
	qDebug()<<"JClientCommandProcessor::process . There should not be any responce.";
}

JType JClientCommandProcessor::getProcessorType()const
{
	return EPI_COMMAND;
}
