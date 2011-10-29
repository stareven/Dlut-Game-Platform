#ifndef JSERVERSOCKETBASE_H
#define JSERVERSOCKETBASE_H

#include "jsocketbase.h"

class JServerSocketBase : public JSocketBase
{
	Q_OBJECT
public:
	// 由JServerBase的子类作为工厂
	explicit JServerSocketBase(QTcpSocket* const socket,QObject *parent = 0);
    void closeConnect();
};

#endif // JSERVERSOCKETBASE_H
