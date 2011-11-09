#include "jmainserverloginprocessor.h"

#include <QDataStream>
#include <QDebug>

#include <Global/Login>
#include <Session/JSession>

#include "service/jloginverification.h"
#include "service/jloginhashcodecreator.h"

JMainServerLoginProcessor::JMainServerLoginProcessor(JSession* session,JSocketBase *socket) :
	JServerNetworkDataProcessorBase(session,socket)
{
}

void JMainServerLoginProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	QString loginname;
	QString passwd;
	JID role;
	stream>>loginname>>passwd>>role;
	JLoginVerification lv;
	JCode code=lv.verification(loginname,passwd,(ERole)role);
	if(0==code){
		JLoginHashCodeCreator lhcc;
		lhcc.setUserId(lv.getUserId());
		getSession()->setUserId(lv.getUserId());
		getSession()->setLoginHashCode(lhcc.createLoginHashCode());
	}
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<code;
	if(0==code){
		outstream<<getSession()->getUserId();
		outstream<<getSession()->getLoginHashCode();
	}
	sendData(outdata);
}

JType JMainServerLoginProcessor::getProcessorType()const
{
	return EPI_LOGIN;
}
