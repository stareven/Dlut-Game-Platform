#ifndef JPSEUDOSERVERSOCKET_H
#define JPSEUDOSERVERSOCKET_H

#include <Socket/JServerSocketBase>

class JPseudoServerSocket : public JServerSocketBase
{
    Q_OBJECT
public:
	explicit JPseudoServerSocket(QTcpSocket* const socket,QObject *parent = 0);

signals:

public slots:

};

#endif // JPSEUDOSERVERSOCKET_H
