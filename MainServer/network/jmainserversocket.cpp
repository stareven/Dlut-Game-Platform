#include "jmainserversocket.h"

#include <Socket/JSession>

JMainServerSocket::JMainServerSocket(QTcpSocket* const socket,QObject *parent) :
	JServerSocketBase(socket,parent)
{
	m_session=new JSession(this);
}

JSession* JMainServerSocket::getSession()const
{
	return m_session;
}
