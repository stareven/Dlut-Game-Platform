#include "jclientsocketbase.h"

#include <QTcpSocket>
#include <QCoreApplication>

#include "../global/shost.h"

JClientSocketBase::JClientSocketBase(QTcpSocket* const socket,QObject *parent) :
	JSocketBase(socket,parent)
{
}

JClientSocketBase* JClientSocketBase::getInstance(){
    static JClientSocketBase* instance=NULL;
    if(NULL==instance){
		instance = new JClientSocketBase(
					new QTcpSocket(QCoreApplication::instance()),
					QCoreApplication::instance());
    }
    return instance;
}
