#include "jmainserversocket.h"

JMainServerSocket::JMainServerSocket(QTcpSocket* const socket,QObject *parent) :
	JServerSocketBase(socket,parent)
{
}
