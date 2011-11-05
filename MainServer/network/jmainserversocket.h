#ifndef JMAINSERVERSOCKET_H
#define JMAINSERVERSOCKET_H

#include <Socket/JServerSocketBase>

class JSession;

class JMainServerSocket : public JServerSocketBase
{
    Q_OBJECT
public:
	explicit JMainServerSocket(QTcpSocket* const socket,QObject *parent = 0);
public:
	JSession* getSession()const;
private:
	JSession* m_session;
};

#endif // JMAINSERVERSOCKET_H
