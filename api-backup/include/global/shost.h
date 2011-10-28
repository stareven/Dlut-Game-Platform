#ifndef SHOST_H
#define SHOST_H

#include <QHostAddress>

#include "globalapi_global.h"

/*!
	\file shost.h
	\brief 定义了 SHost 结构。
*/

struct GLOBALAPISHARED_EXPORT SHost
{
	SHost(const QHostAddress& address=QHostAddress::Null,quint16 port=0);
	QHostAddress m_address;
	quint16 m_port;
	bool isNull()const;
};

#endif // SHOST_H
