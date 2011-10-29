#include "jmainserverloginprocessor.h"

#include <QDataStream>
#include <QDebug>

#include <Global/Login>

#include "service/jloginverification.h"

JMainServerLoginProcessor::JMainServerLoginProcessor(JServerSocketBase *socket) :
	JServerNetworkDataProcessorBase(socket)
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
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<code;
	sendData(outdata);
}

JType JMainServerLoginProcessor::getProcessorType()const
{
	return EPI_LOGIN;
}
