#include "jinformationrequestbase.h"

JInformationRequestBase::JInformationRequestBase(QObject *parent) :
	JInformationRequestByHeadBase(parent)
{
}

void JInformationRequestBase::rqsRemoteMtimeById(JID id)
{
	rqsRemoteMtime(getHeadById(id));
}

bool JInformationRequestBase::waitForRemoteMtimeById(JID id,int msecs)
{
	return waitForRemoteMtime(getHeadById(id),msecs);
}

void JInformationRequestBase::rqsInformationDataById(JID id)
{
	rqsInformationData(getHeadById(id));
}

bool JInformationRequestBase::waitForInformationDataById(JID id,int msecs)
{
	return waitForInformationData(getHeadById(id),msecs);
}

JTime_t JInformationRequestBase::getRemoteMtimeById(JID id)
{
	return getRemoteMtime(getHeadById(id));
}

JTime_t JInformationRequestBase::getLocalMtimeById(JID id)
{
	return getLocalMtime(getHeadById(id));
}

QByteArray JInformationRequestBase::getInformationDataById(JID id)
{
	return getInformationData(getHeadById(id));
}

QByteArray JInformationRequestBase::pullInformationDataById(JID id,int msecs)
{
	return pullInformationData(getHeadById(id),msecs);
}

