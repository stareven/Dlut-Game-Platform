#include "jclientuserregisterprocessor.h"

#include "jmainclientsocket.h"
#include "jsession.h"

JClientUserRegisterProcessor::JClientUserRegisterProcessor(JSession* session,JSocketBase *socket) :
	JClientNetworkDataProcessorBase(session,socket)
{
}

JClientUserRegisterProcessor* JClientUserRegisterProcessor::getInstance()
{
	static JClientUserRegisterProcessor* instance=NULL;
	if(NULL==instance){
		JMainClientSocket* socket=JMainClientSocket::getInstance();
		JSession* session = socket->getSession();
		instance=new JClientUserRegisterProcessor(session,socket);
		socket->registerProcessor(instance);
	}
	return instance;
}

void JClientUserRegisterProcessor::sendRegister(const QString& loginname,const QString& password,ERole role)
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<loginname;
	stream<<password;
	stream<<(JID)role;
	sendData(data);
}

void JClientUserRegisterProcessor::process(const QByteArray &data)
{
	QDataStream stream(data);
	JCode result;
	JID userId;
	QString loginname;
	stream>>result;
	stream>>userId;
	stream>>loginname;
	emit receiveRegisterResult(result,userId,loginname);
}

JType JClientUserRegisterProcessor::getProcessorType()const
{
	return EPI_UserRegister;
}
