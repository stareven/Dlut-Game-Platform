#include "jserverinformationprocessorbase.h"

#include <QDebug>
#include <QDataStream>

#include "../global/jcodeerror.h"
#include "jinformation.h"

using namespace NetworkData;

JServerInformationProcessorBase::JServerInformationProcessorBase(JSession* session,JSocketBase *socket) :
	JServerNetworkDataProcessorBase(session,socket)
{
}

void JServerInformationProcessorBase::process(const QByteArray& data)
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

EProcessorType JServerInformationProcessorBase::getProcessorType()const
{
	return EPI_INFORMATION;
}

void JServerInformationProcessorBase::replyMtime(const JHead& head,JTime_t mtime)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)EIP_DownloadRemoteMtime;
	outstream<<head;
	outstream<<mtime;
	sendData(outdata);
}

void JServerInformationProcessorBase::replyData(const JHead& head,JTime_t currentTime,const QByteArray& data)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)EIP_DownloadData;
	outstream<<head;
	outstream<<currentTime;
	outstream<<data;
	sendData(outdata);
}

void JServerInformationProcessorBase::replyUploadResult(const JHead& head,JCode result)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)EIP_UploadData;
	outstream<<head;
	outstream<<result;
	sendData(outdata);
}
