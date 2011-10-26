#include "jinformationsendbase.h"

#include <QCoreApplication>

#include "../network/jclientuploadinformationprocessor.h"
#include "../global/jelapsedtimer.h"

using namespace NetworkData;

JInformationSendBase::JInformationSendBase(QObject *parent) :
    JRequestBase(parent)
{
	m_processor = JClientUploadInformationProcessor::getInstance();
	connect(m_processor,
			SIGNAL(receiveSendInformationResult(NetworkData::JHead,JCode)),
			SLOT(on_processor_receiveSendInformationResult(NetworkData::JHead,JCode)));
}

void JInformationSendBase::sendInformationData(const JHead& head,const QByteArray& data)
{
	m_sendResults.remove(head);
	m_processor->sendInformationData(head,data);
}

bool JInformationSendBase::waitForSendResult(const JHead& head,int msecs)
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(m_sendResults.contains(head))
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return m_sendResults.contains(head);
}

JCode JInformationSendBase::getSendResult(const JHead& head)
{
	return m_sendResults.value(head,-1);
}

JCode JInformationSendBase::pushInformationData(const JHead& head,const QByteArray& data,int msecs)
{
	sendInformationData(head,data);
	waitForSendResult(head,msecs);
	return getSendResult(head);
}

void JInformationSendBase::sendInformationData(JID id,const QByteArray& data)
{
	sendInformationData(getHead(id),data);
}

bool JInformationSendBase::waitForSendResult(JID id,int msecs)
{
	return waitForSendResult(getHead(id),msecs);
}

JCode JInformationSendBase::getSendResult(JID id)
{
	return getSendResult(getHead(id));
}

JCode JInformationSendBase::pushInformationData(JID id,const QByteArray& data,int msecs)
{
	return pushInformationData(getHead(id),data,msecs);
}

void JInformationSendBase::on_processor_receiveSendInformationResult(const JHead& head,JCode result)
{
	m_sendResults.insert(head,result);
}
