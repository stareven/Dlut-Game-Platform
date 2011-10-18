#include "jclientinformationprocessor.h"

#include "jclientsocketbase.h"

JClientInformationProcessor::JClientInformationProcessor(QObject *parent) :
    JClientNetworkDataProcessorBase(parent)
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

JType JClientInformationProcessor::getProcessorType()const
{
	return EPI_INFORMATION;
}
