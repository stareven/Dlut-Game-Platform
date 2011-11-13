#include "jsnakesocket.h"


#include <QTcpSocket>
#include <QCoreApplication>



JSnakeSocket::JSnakeSocket(QObject *parent) :
	JClientSocketBase(new QTcpSocket(QCoreApplication::instance()),parent)
{
}

JSnakeSocket* JSnakeSocket::getInstance()
{
	static JSnakeSocket* instance = NULL;
	if(NULL==instance){
		instance = new JSnakeSocket(
					QCoreApplication::instance());
	}
	return instance;
}
