#include "jcommandsendbase.h"

#include "../network/jclientcommandprocessor.h"

JCommandSendBase::JCommandSendBase(QObject *parent) :
    JRequestBase(parent)
{
	m_processor = JClientCommandProcessor::getInstance();
}

void JCommandSendBase::sendShutdown()
{
	m_processor->sendCommand(ECT_Shutdown);
}

void JCommandSendBase::sendRestart()
{
	m_processor->sendCommand(ECT_Restart);
}
