#ifndef SHOST_H
#define SHOST_H

#include <QHostAddress>

struct SHost
{
	SHost(const QHostAddress& address=QHostAddress::Null,quint16 port=-1);
	QHostAddress m_address;
	quint16 m_port;
};

#endif // SHOST_H
