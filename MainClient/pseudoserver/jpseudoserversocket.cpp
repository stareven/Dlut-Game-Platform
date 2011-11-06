#include "jpseudoserversocket.h"

JPseudoServerSocket::JPseudoServerSocket(QTcpSocket* const socket,QObject *parent) :
	JServerSocketBase(socket,parent)
{
}
