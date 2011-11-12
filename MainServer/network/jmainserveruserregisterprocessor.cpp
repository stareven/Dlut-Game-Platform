#include "jmainserveruserregisterprocessor.h"
#include "../service/juserregister.h"

#include <QDataStream>

JMainServerUserRegisterProcessor::JMainServerUserRegisterProcessor(JSession* session,JSocketBase *socket) :
	JServerNetworkDataProcessorBase(session,socket)
{
}

void JMainServerUserRegisterProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	QString loginname;
	QString password;
	stream>>loginname;
	stream>>password;
	processUserRegister(loginname,password);
}

EProcessorType JMainServerUserRegisterProcessor::getProcessorType()const
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

void JMainServerUserRegisterProcessor::processUserRegister(const QString& loginname,const QString& password)
{
	JUserRegister ur;
	ur.execute(loginname,password);
	replyRegisterResult(ur.getResult(),ur.getUserId(),ur.getLoginname());
}
