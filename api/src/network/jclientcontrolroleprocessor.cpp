#include "jclientcontrolroleprocessor.h"

#include "jmainclientsocket.h"
#include "jsession.h"

JClientControlRoleProcessor::JClientControlRoleProcessor(JSession* session,JSocketBase *socket) :
	JClientNetworkDataProcessorBase(session,socket)
{
}

JClientControlRoleProcessor* JClientControlRoleProcessor::getInstance()
{
	static JClientControlRoleProcessor* instance=NULL;
	if(NULL==instance){
		JMainClientSocket* socket=JMainClientSocket::getInstance();
		JSession* session = socket->getSession();
		instance=new JClientControlRoleProcessor(session,socket);
		socket->registerProcessor(instance);
	}
	return instance;
}

void JClientControlRoleProcessor::sendControlRole(JID userId,ERole role,EControlRoleAction act)
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<userId;
	stream<<(JID)role;
	stream<<(JID)act;
	sendData(data);
}

void JClientControlRoleProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	JID userId;
	JCode result;
	stream>>userId;
	stream>>result;
	emit receiveControlRoleResult(userId,result);
}

JType JClientControlRoleProcessor::getProcessorType()const
{
	return EPI_ControlRole;
}
