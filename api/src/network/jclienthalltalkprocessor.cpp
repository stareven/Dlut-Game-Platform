#include "jclienthalltalkprocessor.h"

#include "jmainclientsocket.h"
#include "jsession.h"

JClientHallTalkProcessor::JClientHallTalkProcessor(JSession* session,JSocketBase *socket) :
	JClientNetworkDataProcessorBase(session,socket)
{
}

JClientHallTalkProcessor* JClientHallTalkProcessor::getInstance()
{
	static JClientHallTalkProcessor* instance = NULL;
	if(NULL==instance){
		JMainClientSocket* socket=JMainClientSocket::getInstance();
		JSession* session = socket->getSession();
		instance=new JClientHallTalkProcessor(session,socket);
		socket->registerProcessor(instance);
	}
	return instance;
}

void JClientHallTalkProcessor::sendMessage(const QString& msg)
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<msg;
	sendData(data);
}

void JClientHallTalkProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	QString msg;
	stream>>msg;
	emit rcvMessage(msg);
}

EProcessorType JClientHallTalkProcessor::getProcessorType()const
{
	return EPI_HallTalk;
}
