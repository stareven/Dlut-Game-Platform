#include "jclientuserregisterprocessor.h"

#include "jclientsocketbase.h"
#include "jclientsession.h"

JClientUserRegisterProcessor::JClientUserRegisterProcessor(JSession* session,JSocketBase *socket) :
	JClientNetworkDataProcessorBase(session,socket)
{
}

JClientUserRegisterProcessor* JClientUserRegisterProcessor::getInstance()
{
	static JClientUserRegisterProcessor* instance=NULL;
	if(NULL==instance){
		JClientSocketBase* socket=JClientSocketBase::getInstance();
		JClientSession* session = JClientSession::getInstance();
		instance=new JClientUserRegisterProcessor(session,socket);
		socket->registerProcessor(instance);
	}
	return instance;
}

void JClientUserRegisterProcessor::sendRegister(const QString& loginname,const QString& password)
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<loginname;
	stream<<password;
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
