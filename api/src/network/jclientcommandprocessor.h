#ifndef JCLIENTCOMMANDPROCESSOR_H
#define JCLIENTCOMMANDPROCESSOR_H

#include "jclientnetworkdataprocessorbase.h"
#include "../global/command.h"

class JClientCommandProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
	explicit JClientCommandProcessor(JClientSocketBase *socket);
public:
	static JClientCommandProcessor* getInstance();
	void sendCommand(ECommandType type,JID param1=-1);
protected:
	void process(const QByteArray &data);
	JType getProcessorType()const;
};

#endif // JCLIENTCOMMANDPROCESSOR_H
