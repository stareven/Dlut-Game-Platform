#include "jclientuploadinformationprocessor.h"

#include "jclientsocketbase.h"
#include "jinformation.h"

using namespace NetworkData;

JClientUploadInformationProcessor::JClientUploadInformationProcessor(JClientSocketBase *socket) :
	JClientNetworkDataProcessorBase(socket)
{
}

JClientUploadInformationProcessor* JClientUploadInformationProcessor::getInstance()
{
	static JClientUploadInformationProcessor* instance=NULL;
	if(NULL == instance){
		JClientSocketBase* socket=JClientSocketBase::getInstance();
		instance = new JClientUploadInformationProcessor(socket);
		socket->registerProcessor(instance->getProcessorType(),instance);
	}
	return instance;
}

void JClientUploadInformationProcessor::sendInformationData(const JHead& head,const QByteArray& data)
{
	QByteArray outdata;
	QDataStream stream(&outdata,QIODevice::WriteOnly);
	stream<<head;
	stream<<data;
	sendData(outdata);
}

JType JClientUploadInformationProcessor::getProcessorType()const
{
	return EPI_UPLOADINFORMATION;
}

void JClientUploadInformationProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	JHead head;
	JCode result;
	stream>>head;
	stream>>result;
	emit receiveSendInformationResult(head,result);
}
