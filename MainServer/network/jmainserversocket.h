#ifndef JMAINSERVERSOCKET_H
#define JMAINSERVERSOCKET_H

#include <Socket/JServerSocketBase>

class JMainServerSocket : public JServerSocketBase
{
    Q_OBJECT
public:
	explicit JMainServerSocket(QTcpSocket* const socket,QObject *parent = 0);
};

#endif // JMAINSERVERSOCKET_H
