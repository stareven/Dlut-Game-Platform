#include "jmainserverdownloadinformationprocessor.h"

#include <QDebug>

#include <QDataStream>

#include "service/jmainserverinformationmanager.h"

using namespace NetworkData;

JMainServerDownloadInformationProcessor::JMainServerDownloadInformationProcessor(JServerSocketBase *socket)
	:JServerNetworkDataProcessorBase(socket),
	m_im(JMainServerInformationManager::getInstance())
{
}

void JMainServerDownloadInformationProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	JID protocol;
	JHead head;
	stream>>protocol;
	stream>>head;
	switch(protocol){
	case EIP_RemoteMtime:
		sendInformationMtime(head);
		break;
	case EIP_Data:
		sendInformationData(head);
		break;
	default:
		qDebug()<<"no such protocol!"<<protocol;
		break;
	}
}

JType JMainServerDownloadInformationProcessor::getProcessorType()const
{
	return EPI_DOWNLOADINFORMATION;
}

void JMainServerDownloadInformationProcessor::sendInformationMtime(const JHead& head)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)EIP_RemoteMtime;
	outstream<<head;
	outstream<<m_im.getMtime(head);
	sendData(outdata);
}

void JMainServerDownloadInformationProcessor::sendInformationData(const JHead& head)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)EIP_Data;
	outstream<<head;
	outstream<<m_im.getCurrentTime();
	outstream<<m_im.getData(head);
	sendData(outdata);
}
