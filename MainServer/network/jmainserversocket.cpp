#include "jmainserversocket.h"

#include <Socket/JSession>

JMainServerSocket::JMainServerSocket(QTcpSocket* const socket,QObject *parent) :
	JServerSocketBase(socket,parent)
{
}
