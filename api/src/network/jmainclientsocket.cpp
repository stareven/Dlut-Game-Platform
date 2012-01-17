#include "jmainclientsocket.h"

#include <QTcpSocket>
#include <QCoreApplication>

/*!
    \class JMainClientSocket jmainclientsocket.h <Socket/JMainClientSocket>
    \ingroup socket
    \brief 主客户端套接字
*/

JMainClientSocket::JMainClientSocket(QObject *parent) :
	JClientSocketBase(new QTcpSocket(QCoreApplication::instance()),parent)
{
}

/*!
    \brief 静态单例方法

    外部只能通过此函数获得这个类的实例。
*/
JMainClientSocket* JMainClientSocket::getInstance(){
	static JMainClientSocket* instance=NULL;
	if(NULL==instance){
		instance = new JMainClientSocket(
					QCoreApplication::instance());
	}
	return instance;
}
