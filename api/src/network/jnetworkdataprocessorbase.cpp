#include "jnetworkdataprocessorbase.h"

#include "jsocketbase.h"

JNetworkDataProcessorBase::JNetworkDataProcessorBase (JSession* session,JSocketBase *socket)
	:QObject(socket),
	m_socket(socket),
	m_session(session)
{

}

JCode JNetworkDataProcessorBase::sendData(const QByteArray& data)
{
	return m_socket->sendData(getProcessorType(),data);
}

JSession* JNetworkDataProcessorBase::getSession()const
{
	return m_session;
}
