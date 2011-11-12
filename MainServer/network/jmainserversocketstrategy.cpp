#include "jmainserversocketstrategy.h"

#include <Global/Processor>
#include <Socket/JSocketBase>
#include <Session/JSession>

#include <QCoreApplication>

JMainServerSocketStrategy::JMainServerSocketStrategy(QObject *parent) :
    JSocketStrategy(parent)
{
}

JMainServerSocketStrategy* JMainServerSocketStrategy::getInstance()
{
	static JMainServerSocketStrategy* instance=NULL;
	if(NULL == instance){
		instance = new JMainServerSocketStrategy(QCoreApplication::instance());
	}
	return instance;
}

bool JMainServerSocketStrategy::filterBeforeProcess(JSocketBase* socket)
{
	JID userId = socket->getSession()->getUserId();
	if(userId < 0){
		switch(socket->getType()){
		case EPI_LOGIN:
		case EPI_UserRegister:
			return true;
			break;
		case EPI_INFORMATION:
		case EPI_COMMAND:
			socket->closeConnect();
			return false;
			break;
		}
	}else{
		return true;
	}
	return true;
}
