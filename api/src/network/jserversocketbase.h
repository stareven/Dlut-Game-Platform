#ifndef JSERVERSOCKETBASE_H
#define JSERVERSOCKETBASE_H

#include "jsocketbase.h"

/*!
    \file jserversocketbase.h
    \ingroup socket
    \brief 定义了 JServerSocketBase 类
*/

class JServerSocketBase : public JSocketBase
{
	Q_OBJECT
public:
	explicit JServerSocketBase(QTcpSocket* const socket,QObject *parent = 0);
};

#endif // JSERVERSOCKETBASE_H
