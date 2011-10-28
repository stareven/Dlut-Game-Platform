#ifndef JSERVERSOCKETBASE_H
#define JSERVERSOCKETBASE_H

#include "jsocketbase.h"

class JServerSocketBase : public JSocketBase
{
    Q_OBJECT
    JServerSocketBase(const JServerSocketBase&);
    JServerSocketBase& operator=(const JServerSocketBase&);
    explicit JServerSocketBase(QTcpSocket* const socket,QObject *parent = 0);
public:
	// MainServer和GameServer产生的JServerSocketBase显然是不一样的，工厂不应该在这里产生
	// static JServerSocketBase* create();
    void closeConnect();
};

#endif // JSERVERSOCKETBASE_H
