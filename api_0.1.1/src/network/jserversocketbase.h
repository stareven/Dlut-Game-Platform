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
    static JServerSocketBase* create();
    void closeConnect();
};

#endif // JSERVERSOCKETBASE_H
