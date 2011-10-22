#include "jinformationrequestbase.h"

#include <QCoreApplication>

#include "jclientdownloadinformationprocessor.h"
#include "../global/jelapsedtimer.h"
#include "jinformationmanager.h"

using namespace NetworkData;

JInformationRequestBase::JInformationRequestBase(QObject *parent) :
    JRequestBase(parent)
{
	m_processor = JClientDownloadInformationProcessor::getInstance();
	connect(m_processor,
			SIGNAL(receiveData(NetworkData::JHead,JTime_t,QByteArray)),
			SLOT(on_processor_receiveData(NetworkData::JHead,JTime_t,QByteArray)));
	connect(m_processor,
			SIGNAL(receiveRemoteMtime(NetworkData::JHead,JTime_t)),
			SLOT(on_processor_receiveRemoteMtime(NetworkData::JHead,JTime_t)));
}

void JInformationRequestBase::rqsRemoteMtime(const NetworkData::JHead& head)
{
	m_receivedRemoteMtime.remove(head);
	m_processor->requestInformationRemoteMtime(head);
}

bool JInformationRequestBase::waitForRemoteMtime(const NetworkData::JHead& head,int msec)
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msec)
	{
		if(m_receivedRemoteMtime.contains(head))
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return m_receivedRemoteMtime.contains(head);
}

void JInformationRequestBase::rqsInformationData(const NetworkData::JHead& head)
{
	m_receivedInformationData.remove(head);
	m_processor->requestInformationData(head);
}

bool JInformationRequestBase::waitForInformationData(const NetworkData::JHead& head,int msec)
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msec)
	{
		if(m_receivedInformationData.contains(head))
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return m_receivedInformationData.contains(head);
}

JTime_t JInformationRequestBase::getRemoteMtime(const NetworkData::JHead& head)
{
	return JInformationManager::getInstance().getInformation(head).getRemoteMtime();
}

JTime_t JInformationRequestBase::getLocalMtime(const NetworkData::JHead& head)
{
	return JInformationManager::getInstance().getInformation(head).getLocalMtime();
}

QByteArray JInformationRequestBase::getInformationData(const NetworkData::JHead& head)
{
	return JInformationManager::getInstance().getInformation(head).getData();
}

QByteArray JInformationRequestBase::pullInformationData(const NetworkData::JHead& head,int msec)
{
	rqsRemoteMtime(head);
	if(waitForRemoteMtime(msec/2)){
		if(getRemoteMtime(head)>getLocalMtime(head)){
			rqsInformationData(head);
			waitForInformationData(head,msec/2);
		}
	}
	return getInformationData(head);
}

void JInformationRequestBase::rqsRemoteMtime(JID id)
{
	rqsRemoteMtime(getHead(id));
}

bool JInformationRequestBase::waitForRemoteMtime(JID id,int msec)
{
	return waitForRemoteMtime(getHead(id),msec);
}

void JInformationRequestBase::rqsInformationData(JID id)
{
	rqsInformationData(getHead(id));
}

bool JInformationRequestBase::waitForInformationData(JID id,int msec)
{
	return waitForInformationData(getHead(id),msec);
}

JTime_t JInformationRequestBase::getRemoteMtime(JID id)
{
	return getRemoteMtime(getHead(id));
}

JTime_t JInformationRequestBase::getLocalMtime(JID id)
{
	return getLocalMtime(getHead(id));
}

QByteArray JInformationRequestBase::getInformationData(JID id)
{
	return getInformationData(getHead(id));
}

QByteArray JInformationRequestBase::pullInformationData(JID id,int msec)
{
	return pullInformationData(getHead(id),msec);
}

void JInformationRequestBase::on_processor_receiveRemoteMtime(const NetworkData::JHead& head,JTime_t)
{
	m_receivedRemoteMtime.insert(head);
}

void JInformationRequestBase::on_processor_receiveData(const NetworkData::JHead& head,JTime_t,const QByteArray&)
{
	m_receivedInformationData.insert(head);
}
