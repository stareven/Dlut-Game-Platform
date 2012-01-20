#include "jserversocketbase.h"

/*!
    \class JServerSocketBase jserversocketbase.h <Socket/JServerSocketBase>
    \ingroup socket
    \brief 服务器端套接字基类
*/

/*!
    \brief 构造函数

    子类应提供工厂方法。
*/
JServerSocketBase::JServerSocketBase(QTcpSocket* const socket,QObject *parent) :
    JSocketBase(socket,parent)
{
}
