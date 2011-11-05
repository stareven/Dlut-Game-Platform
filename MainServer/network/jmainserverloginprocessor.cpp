#include "jmainserverloginprocessor.h"

#include <QDataStream>
#include <QDebug>

#include <Global/Login>
#include <Socket/JSession>

#include "service/jloginverification.h"
#include "jmainserversocket.h"

JMainServerLoginProcessor::JMainServerLoginProcessor(JMainServerSocket *socket) :
	JServerNetworkDataProcessorBase(socket->getSession(),socket)
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
		getSession()->setUserId(lv.getUserId());
	}
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<code;
	sendData(outdata);
}

JType JMainServerLoginProcessor::getProcessorType()const
{
	return EPI_LOGIN;
}
