#include "jmainserverhalltalkprocessor.h"

#include "service/jhalltalkbroadcaster.h"

#include <QDataStream>

JMainServerHallTalkProcessor::JMainServerHallTalkProcessor(JSession* session,JSocketBase *socket) :
	JServerNetworkDataProcessorBase(session,socket)
{
	JHallTalkBroadcaster* htb = JHallTalkBroadcaster::getInstance();
	connect(this,SIGNAL(rcvMessage(QString)),htb,SIGNAL(rcvMessage(QString)));
	connect(htb,SIGNAL(rcvMessage(QString)),SLOT(sendMessage(QString)));
}

void JMainServerHallTalkProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	QString msg;
	stream>>msg;
	emit rcvMessage(msg);
}

EProcessorType JMainServerHallTalkProcessor::getProcessorType()const
{
	return EPI_HallTalk;
}

void JMainServerHallTalkProcessor::sendMessage(const QString& msg)
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<msg;
	sendData(data);
}
