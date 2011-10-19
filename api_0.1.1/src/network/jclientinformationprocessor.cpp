#include "jclientinformationprocessor.h"

#include "jclientsocketbase.h"
#include "jinformation.h"
#include "jinformationmanager.h"

using namespace NetworkData;

JClientInformationProcessor::JClientInformationProcessor(JClientSocketBase *socket) :
	JClientNetworkDataProcessorBase(socket)
{
}

JClientInformationProcessor* JClientInformationProcessor::getInstance()
{
	static JClientInformationProcessor* instance = NULL;
	if(NULL == instance){
		JClientSocketBase* socket=JClientSocketBase::getInstance();
		instance = new JClientInformationProcessor(socket);
		socket->registerProcessor(instance->getProcessorType(),instance);
	}
	return instance;
}

void JClientInformationProcessor::requestInformationRemoteMtime(const JHead& head)
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<(JID)EIP_RemoteMtime;
	stream<<head;
	getSocket()->sendData(getProcessorType(),data);
}

void JClientInformationProcessor::requestInformationData(const JHead& head)
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<(JID)EIP_Data;
	stream<<head;
	getSocket()->sendData(getProcessorType(),data);
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
