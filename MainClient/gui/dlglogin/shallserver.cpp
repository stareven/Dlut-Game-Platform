#include "shallserver.h"

SHallServer::SHallServer()
{
    updateString();
}

SHallServer::SHallServer(const QHostAddress& address,quint16 port)
	:m_address(address),m_port(port)
{
    updateString();
}

const QString& SHallServer::toString()const
{
    return m_string;
}

const QHostAddress& SHallServer::getAddress()const
{
    return m_address;
}

quint16 SHallServer::getPort()const
{
    return m_port;
}

SHallServer::operator SHost()const
{
	return SHost(getAddress(),getPort());
}

//const QString& SHallServer::getName()const
//{
//    return m_name;
//}

//void SHallServer::setName(const QString& name)
//{
//    m_name=name;
//    updateString();
//}

bool SHallServer::isEmpty()const
{
    if(m_address.isNull() || m_port==0) return true;
    else return false;
}

void SHallServer::updateString()
{
	m_string=QString("%1:%2").arg(m_address.toString()).arg(m_port);
}
