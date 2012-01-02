#include "jmainserveruserregisterprocessor.h"
#include "../service/juserregister.h"

#include <QDataStream>
#include <Global/Login>
#include <Global/CodeError>
#include <Session/JSession>
#include <Global/Register>

JMainServerUserRegisterProcessor::JMainServerUserRegisterProcessor(JSession* session,JSocketBase *socket) :
	JServerNetworkDataProcessorBase(session,socket)
{
}

void JMainServerUserRegisterProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	QString loginname;
	QString password;
	JID role;
	stream>>loginname;
	stream>>password;
	stream>>role;
	processUserRegister(loginname,password,role);
}

JType JMainServerUserRegisterProcessor::getProcessorType()const
{
	return EPI_UserRegister;
}

void JMainServerUserRegisterProcessor::replyRegisterResult(JCode result,JID userId,const QString& loginname)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<result;
	outstream<<userId;
	outstream<<loginname;
	sendData(outdata);
}

void JMainServerUserRegisterProcessor::processUserRegister(const QString& loginname,const QString& password,JID role)
{
	if(role<0 || role > ROLE_ROOT){
		replyRegisterResult(ER_RoleOverflow,-1,loginname);
		return;
	}
	JUserRegister ur(getSession()->getUserId());
	ur.execute(loginname,password,(ERole)role);
	replyRegisterResult(ur.getResult(),ur.getUserId(),ur.getLoginname());
}
