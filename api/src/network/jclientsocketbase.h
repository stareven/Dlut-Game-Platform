#ifndef JCLIENTSOCKETBASE_H
#define JCLIENTSOCKETBASE_H

#include "jsocketbase.h"

/*!
    \file jclientsocketbase.h
    \ingroup socket
    \brief 定义了 JClientSocketBase 类
*/

class JClientSocketBase : public JSocketBase
{
    Q_OBJECT
protected:
	explicit JClientSocketBase(QTcpSocket* const socket,QObject *parent = 0);
};

#endif // JCLIENTSOCKETBASE_H
