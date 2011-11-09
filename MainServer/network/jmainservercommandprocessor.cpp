#include "jmainservercommandprocessor.h"

#include "service/jpermissioncontrol.h"
#include "service/jcommandmanager.h"
#include "jmainserversocket.h"

#include <Session/JSession>

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
	JPermissionControl pc(getSession()->getUserId());
	if(pc.checkCommand(type,param)){
		JCommandManager cm;
		cm.executeCommand(type,param);
	}
}

JType JMainServerCommandProcessor::getProcessorType()const
{
	return EPI_COMMAND;
}
