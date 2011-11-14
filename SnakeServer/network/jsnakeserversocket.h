#ifndef JSNAKESERVERSOCKET_H
#define JSNAKESERVERSOCKET_H

#include <Socket/JServerSocketBase>

class JSnakeServerSocket : public JServerSocketBase
{
    Q_OBJECT
public:
	explicit JSnakeServerSocket(QTcpSocket* const socket,QObject *parent = 0);

signals:

public slots:

};

#endif // JSNAKESERVERSOCKET_H
