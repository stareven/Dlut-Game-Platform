#include "jmainserverinformationprocessor.h"

#include <QDebug>

#include <QDataStream>

#include "service/jmainserverinformationmanager.h"

using namespace NetworkData;

JMainServerInformationProcessor::JMainServerInformationProcessor(JServerSocketBase *socket) :
	JServerNetworkDataProcessorBase(socket),
	m_im(JMainServerInformationManager::getInstance())
{
}

void JMainServerInformationProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	JID protocol;
	JHead head;
	QByteArray uploadData;
	stream>>protocol;
	stream>>head;
	switch(protocol){
	case EIP_DownloadRemoteMtime:
		processDownloadRemoteMtime(head);
		break;
	case EIP_DownloadData:
		processDownloadData(head);
		break;
	case EIP_UploadData:
		stream>>uploadData;
		processUploadData(head,uploadData);
		break;
	default:
		qDebug()<<"no such protocol!"<<protocol;
		break;
	}
}

JType JMainServerInformationProcessor::getProcessorType()const
{
	return EPI_INFORMATION;
}

void JMainServerInformationProcessor::replyMtime(const JHead& head,JTime_t mtime)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)EIP_DownloadRemoteMtime;
	outstream<<head;
	outstream<<mtime;
	sendData(outdata);
}

void JMainServerInformationProcessor::replyData(const JHead& head,JTime_t currentTime,const QByteArray& data)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)EIP_DownloadData;
	outstream<<head;
	outstream<<currentTime;
	outstream<<data;
	sendData(outdata);
}

void JMainServerInformationProcessor::replyUploadResult(const JHead& head,JCode result)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)EIP_UploadData;
	outstream<<head;
	outstream<<result;
	sendData(outdata);
}

void JMainServerInformationProcessor::processDownloadRemoteMtime(const JHead& head)
{
	replyMtime(head,m_im.getMtime(head));
}

void JMainServerInformationProcessor::processDownloadData(const JHead& head)
{
	replyData(head,m_im.getCurrentTime(),m_im.getData(head));
}

void JMainServerInformationProcessor::processUploadData(const JHead& head,const QByteArray& uploadData)
{
	replyUploadResult(head,m_im.updateData(head,uploadData));
}
