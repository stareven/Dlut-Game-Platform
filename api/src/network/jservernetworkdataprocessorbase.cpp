#include "jservernetworkdataprocessorbase.h"

#include "jserversocketbase.h"

JServerNetworkDataProcessorBase::JServerNetworkDataProcessorBase(JServerSocketBase *socket)
	:JNetworkDataProcessorBase(socket),
	m_socket(socket)
{
}

void JServerNetworkDataProcessorBase::sendData(const QByteArray& data)
{
	m_socket->sendData(getProcessorType(),data);
}
