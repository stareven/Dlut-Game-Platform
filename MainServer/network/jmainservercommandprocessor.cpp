#include "jmainservercommandprocessor.h"

#include "service/jpermissioncontrol.h"
#include "service/jcommandmanager.h"
#include "jmainserversocket.h"

#include <Session/JSession>
#include <Global/CodeError>

#include <QDataStream>

JMainServerCommandProcessor::JMainServerCommandProcessor(JSession* session,JSocketBase *socket) :
	JServerNetworkDataProcessorBase(session,socket)
{
}

void JMainServerCommandProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	JID type;
	JID param;
	stream>>type;
	stream>>param;
	processCommand(type,param);
}

JType JMainServerCommandProcessor::getProcessorType()const
{
	return EPI_COMMAND;
}

void JMainServerCommandProcessor::processCommand(JID type,JID param)
{
	JPermissionControl pc(getSession()->getUserId());
	if(pc.checkCommand(type,param)){
		JCommandManager cm;
		cm.executeCommand(type,param);
		replyCommandResult(type,ESuccess);
	}else{
		replyCommandResult(type,EPermissionDenied);
	}
}

void JMainServerCommandProcessor::replyCommandResult(JID type,JCode result)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<type;
	outstream<<result;
	sendData(outdata);
}
