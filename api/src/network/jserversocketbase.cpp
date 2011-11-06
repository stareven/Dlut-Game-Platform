#include "jserversocketbase.h"

#include "jsession.h"

JServerSocketBase::JServerSocketBase(QTcpSocket* const socket,QObject *parent) :
    JSocketBase(socket,parent)
{
	m_session=new JSession(this);
}

JSession* JServerSocketBase::getSession()const
{
	return m_session;
}
