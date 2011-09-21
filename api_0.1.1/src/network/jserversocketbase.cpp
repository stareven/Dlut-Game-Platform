#include "jserversocketbase.h"

JServerSocketBase::JServerSocketBase(QTcpSocket* const socket,QObject *parent) :
    JSocketBase(socket,parent)
{
}

/*!
    factory
*/
JServerSocketBase* JServerSocketBase::create(){
    return NULL;
}
