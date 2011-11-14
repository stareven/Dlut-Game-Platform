#include "jsnakeserversocket.h"

JSnakeServerSocket::JSnakeServerSocket(QTcpSocket* const socket,QObject *parent) :
	JServerSocketBase(socket,parent)
{
}
