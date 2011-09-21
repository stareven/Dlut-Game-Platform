#ifndef JCLIENTSOCKETBASE_H
#define JCLIENTSOCKETBASE_H

#include "jsocketbase.h"

class SHost;

class JClientSocketBase : public JSocketBase
{
    Q_OBJECT
    JClientSocketBase(const JClientSocketBase&);
    JClientSocketBase& operator=(const JClientSocketBase&);
protected:
    explicit JClientSocketBase(QTcpSocket* const socket,QObject *parent = 0);
public:
    static JClientSocketBase* getInstance();
    void connectToServer(const SHost&);
};

#endif // JCLIENTSOCKETBASE_H
