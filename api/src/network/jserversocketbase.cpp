#include "jserversocketbase.h"

JServerSocketBase::JServerSocketBase(QTcpSocket* const socket,QObject *parent) :
    JSocketBase(socket,parent)
{
}

