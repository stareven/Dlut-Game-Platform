#include "jmainserveruploadinformationprocessor.h"

#include <QDebug>

#include <QDataStream>

#include "service/jmainserverinformationmanager.h"

using namespace NetworkData;

JMainServerUploadInformationProcessor::JMainServerUploadInformationProcessor(JServerSocketBase *socket) :
	JServerNetworkDataProcessorBase(socket),
	m_im(JMainServerInformationManager::getInstance())
{
}

void JMainServerUploadInformationProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	JHead head;
	QByteArray informationData;
	stream>>head;
	stream>>informationData;
	JCode result = m_im.updateData(head,informationData);
	sendUploadResult(head,result);
}

JType JMainServerUploadInformationProcessor::getProcessorType()const
{
	return EPI_UPLOADINFORMATION;
}

void JMainServerUploadInformationProcessor::sendUploadResult(const NetworkData::JHead& head,JCode result)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<head;
	outstream<<result;
	sendData(outdata);
}
