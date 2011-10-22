#include "jclientdownloadinformationprocessor.h"

#include "jclientsocketbase.h"
#include "jinformation.h"
#include "jinformationmanager.h"

using namespace NetworkData;

JClientDownloadInformationProcessor::JClientDownloadInformationProcessor(JClientSocketBase *socket) :
	JClientNetworkDataProcessorBase(socket)
{
}

JClientDownloadInformationProcessor* JClientDownloadInformationProcessor::getInstance()
{
	static JClientDownloadInformationProcessor* instance = NULL;
	if(NULL == instance){
		JClientSocketBase* socket=JClientSocketBase::getInstance();
		instance = new JClientDownloadInformationProcessor(socket);
		socket->registerProcessor(instance->getProcessorType(),instance);
	}
	return instance;
}

void JClientDownloadInformationProcessor::requestInformationRemoteMtime(const JHead& head)
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<(JID)EIP_RemoteMtime;
	stream<<head;
	sendData(data);
}

void JClientDownloadInformationProcessor::requestInformationData(const JHead& head)
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<(JID)EIP_Data;
	stream<<head;
	sendData(data);
}

JType JClientDownloadInformationProcessor::getProcessorType()const
{
	return EPI_INFORMATION;
}

void JClientDownloadInformationProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	JID protocol;
	stream>>protocol;
	if(protocol>=0 && protocol<NetworkData::EIP_Max){
		switch((EInformationProtocol)protocol){
		case EIP_RemoteMtime:
		{
			JHead head;
			JTime_t remoteMtime;
			stream>>head;
			stream>>remoteMtime;
			JInformationManager::getInstance().setRemoteMtime(head,remoteMtime);
			emit receiveRemoteMtime(head,remoteMtime);
		}
			break;
		case EIP_Data:
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
