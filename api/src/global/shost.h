#ifndef SHOST_H
#define SHOST_H

#include <QHostAddress>

/*!
	\file shost.h
	\ingroup global
	\brief 定义了 SHost 结构体。
*/

struct SHost
{
	SHost(const QHostAddress& address=QHostAddress::Null,quint16 port=0);
	QHostAddress m_address;
	quint16 m_port;
	bool isNull()const;
};

#endif // SHOST_H
