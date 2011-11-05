#include "jmainservercommandprocessor.h"

#include "service/jcommandmanager.h"

#include <QDataStream>

JMainServerCommandProcessor::JMainServerCommandProcessor(JServerSocketBase *socket) :
	JServerNetworkDataProcessorBase(socket)
{
}

void JMainServerCommandProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	JID type;
	JID param;
	stream>>type;
	stream>>param;
	JCommandManager cm;
	cm.executeCommand(type,param);
}

JType JMainServerCommandProcessor::getProcessorType()const
{
	return EPI_COMMAND;
}
