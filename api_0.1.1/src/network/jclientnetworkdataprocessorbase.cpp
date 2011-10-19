#include "jclientnetworkdataprocessorbase.h"

#include "jclientsocketbase.h"

JClientNetworkDataProcessorBase::JClientNetworkDataProcessorBase(JClientSocketBase *socket) :
	JNetworkDataProcessorBase(socket)
{
	setSocket(socket);
}

void JClientNetworkDataProcessorBase::setSocket(JClientSocketBase* socket)
{
	m_socket=socket;
}

JClientSocketBase* JClientNetworkDataProcessorBase::getSocket()const
{
	return m_socket;
}
