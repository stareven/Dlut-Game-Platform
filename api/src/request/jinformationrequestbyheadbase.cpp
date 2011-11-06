#include "jinformationrequestbyheadbase.h"

#include <QCoreApplication>

#include "../network/jclientinformationprocessor.h"
#include "../global/jelapsedtimer.h"
#include "../network/jinformationmanager.h"

using namespace NetworkData;

JInformationRequestByHeadBase::JInformationRequestByHeadBase(QObject *parent) :
    JRequestBase(parent)
{
	m_processor = JClientInformationProcessor::getInstance();
	connect(m_processor,
			SIGNAL(receiveData(NetworkData::JHead,JTime_t,QByteArray)),
			SLOT(on_processor_receiveData(NetworkData::JHead,JTime_t,QByteArray)));
	connect(m_processor,
			SIGNAL(receiveRemoteMtime(NetworkData::JHead,JTime_t)),
			SLOT(on_processor_receiveRemoteMtime(NetworkData::JHead,JTime_t)));
	m_lastLocalMtime=0;
}

void JInformationRequestByHeadBase::rqsRemoteMtime(const NetworkData::JHead& head)
{
	m_receivedRemoteMtime.remove(head);
	m_processor->requestDownloadRemoteMtime(head);
}

bool JInformationRequestByHeadBase::waitForRemoteMtime(const NetworkData::JHead& head,int msecs)
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(m_receivedRemoteMtime.contains(head))
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return m_receivedRemoteMtime.contains(head);
}

void JInformationRequestByHeadBase::rqsInformationData(const NetworkData::JHead& head)
{
	m_receivedInformationData.remove(head);
	m_processor->requestDownloadData(head);
}

bool JInformationRequestByHeadBase::waitForInformationData(const NetworkData::JHead& head,int msecs)
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(m_receivedInformationData.contains(head))
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return m_receivedInformationData.contains(head);
}

JTime_t JInformationRequestByHeadBase::getRemoteMtime(const NetworkData::JHead& head)
{
	return JInformationManager::getInstance().getInformation(head).getRemoteMtime();
}

JTime_t JInformationRequestByHeadBase::getLocalMtime(const NetworkData::JHead& head)
{
	return JInformationManager::getInstance().getInformation(head).getLocalMtime();
}

JTime_t JInformationRequestByHeadBase::getLastLocalMtime()const
{
	return m_lastLocalMtime;
}

QByteArray JInformationRequestByHeadBase::getInformationData(const NetworkData::JHead& head)
{
	return JInformationManager::getInstance().getInformation(head).getData();
}

QByteArray JInformationRequestByHeadBase::pullInformationData(const NetworkData::JHead& head,int msecs)
{
	rqsRemoteMtime(head);
	if(waitForRemoteMtime(head,msecs/2)){
		if(getRemoteMtime(head)>getLocalMtime(head)){
			rqsInformationData(head);
			waitForInformationData(head,msecs/2);
		}
	}
	return getInformationData(head);
}

void JInformationRequestByHeadBase::on_processor_receiveRemoteMtime(const NetworkData::JHead& head,JTime_t)
{
	m_receivedRemoteMtime.insert(head);
}

void JInformationRequestByHeadBase::on_processor_receiveData(const NetworkData::JHead& head,JTime_t localMtime,const QByteArray&)
{
	m_lastLocalMtime=localMtime;
	m_receivedInformationData.insert(head);
}
