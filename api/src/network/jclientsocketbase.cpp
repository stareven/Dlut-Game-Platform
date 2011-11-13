#include "jclientsocketbase.h"



#include "../global/shost.h"

JClientSocketBase::JClientSocketBase(QTcpSocket* const socket,QObject *parent) :
	JSocketBase(socket,parent)
{
}
