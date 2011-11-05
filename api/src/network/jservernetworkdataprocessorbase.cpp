#include "jservernetworkdataprocessorbase.h"

#include "jserversocketbase.h"

JServerNetworkDataProcessorBase::JServerNetworkDataProcessorBase(JSession* session,JServerSocketBase *socket)
	:JNetworkDataProcessorBase(socket),
	m_socket(socket),
	m_session(session)
{
}

void JServerNetworkDataProcessorBase::sendData(const QByteArray& data)
{
	m_socket->sendData(getProcessorType(),data);
}

JSession* JServerNetworkDataProcessorBase::getSession()const
{
	return m_session;
}
