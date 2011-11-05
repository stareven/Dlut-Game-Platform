#include "jsession.h"

JSession::JSession(QObject *parent) :
    QObject(parent)
{
	m_userId=-1;
}

JID JSession::getUserId()const
{
	return m_userId;
}

void JSession::setUserId(JID userId)
{
	m_userId=userId;
}
