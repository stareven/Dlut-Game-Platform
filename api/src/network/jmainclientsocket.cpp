#include "jmainclientsocket.h"

#include <QTcpSocket>
#include <QCoreApplication>

JMainClientSocket::JMainClientSocket(QObject *parent) :
	JClientSocketBase(new QTcpSocket(QCoreApplication::instance()),parent)
{
}

JMainClientSocket* JMainClientSocket::getInstance(){
	static JMainClientSocket* instance=NULL;
	if(NULL==instance){
		instance = new JMainClientSocket(
					QCoreApplication::instance());
	}
	return instance;
}
