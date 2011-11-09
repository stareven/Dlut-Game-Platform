#include "jmainserversocket.h"

#include <Session/JSession>

JMainServerSocket::JMainServerSocket(QTcpSocket* const socket,QObject *parent) :
	JServerSocketBase(socket,parent)
{
}
