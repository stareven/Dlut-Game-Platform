#include "jclientsession.h"

#include "jclientsocketbase.h"

JClientSession::JClientSession(QObject *parent)
	:JSession(parent)
{
}

JClientSession* JClientSession::getInstance()
{
	static JClientSession* instance=NULL;
	if(NULL==instance){
		JClientSocketBase* socket = JClientSocketBase::getInstance();
		instance = new JClientSession(socket);
	}
	return instance;
}
