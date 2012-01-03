#include "jclientinformationprocessor.h"

#include "jmainclientsocket.h"
#include "../global/jhead.h"
#include "jinformationmanager.h"
#include "jsession.h"

using namespace NetworkData;

JClientInformationProcessor::JClientInformationProcessor(JSession* session,JSocketBase *socket) :
	JClientNetworkDataProcessorBase(session,socket)
{
}

JClientInformationProcessor* JClientInformationProcessor::getInstance()
{
	static JClientInformationProcessor* instance=NULL;
	if(NULL == instance){
		JMainClientSocket* socket = JMainClientSocket::getInstance();
		JSession* session = socket->getSession();
		instance = new JClientInformationProcessor(session,socket);
		socket->registerProcessor(instance);
	}
	return instance;
}

void JClientInformationProcessor::requestDownloadRemoteMtime(const JHead& head)
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<(JID)EIP_DownloadRemoteMtime;
	stream<<head;
	sendData(data);
}

void JClientInformationProcessor::requestDownloadData(const JHead& head)
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<(JID)EIP_DownloadData;
	stream<<head;
	sendData(data);
}

void JClientInformationProcessor::requestUploadData(const JHead& head,const QByteArray& data)
{
	QByteArray outdata;
	QDataStream stream(&outdata,QIODevice::WriteOnly);
	stream<<(JID)EIP_UploadData;
	stream<<head;
	stream<<data;
	sendData(outdata);
}

JType JClientInformationProcessor::getProcessorType()const
{
	return EPI_INFORMATION;
}

void JClientInformationProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	JID protocol;
	stream>>protocol;
	if(protocol>=0 && protocol<NetworkData::EIP_Max){
		switch((EInformationProtocol)protocol){
		case EIP_DownloadRemoteMtime:
			{
				JHead head;
				JTime_t remoteMtime;
				stream>>head;
				stream>>remoteMtime;
				JInformationManager::getInstance().setRemoteMtime(head,remoteMtime);
				emit receiveRemoteMtime(head,remoteMtime);
			}
			break;
		case EIP_DownloadData:
			{
				JHead head;
				JTime_t localMtime;
				QByteArray data;
				stream>>head;
				stream>>localMtime;
				stream>>data;
				JInformationManager::getInstance().setLocalMtime(head,localMtime);
				JInformationManager::getInstance().setData(head,data);
				emit receiveData(head,localMtime,data);
			}
			break;
		case EIP_UploadData:
			{
				JHead head;
				JCode result;
				stream>>head;
				stream>>result;
				emit receiveUploadResult(head,result);
			}
			break;
		case EIP_Max:
			qDebug()<<"JClientInformationProcessor::process :"
					   "EInformationProtocol error :"<<protocol;
			break;
		}
	}else{
		qDebug()<<"JClientInformationProcessor::process :"
				   "EInformationProtocol error :"<<protocol;
	}
}
