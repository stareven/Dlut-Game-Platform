#include "global/shost.h"

SHost::SHost(const QHostAddress& address,quint16 port)
{
	m_address=address;
	m_port=port;
}
