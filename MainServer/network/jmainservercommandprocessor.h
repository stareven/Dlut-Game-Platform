#ifndef JMAINSERVERCOMMANDPROCESSOR_H
#define JMAINSERVERCOMMANDPROCESSOR_H

#include <Processor/JServerNetworkDataProcessorBase>

class JMainServerCommandProcessor : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JMainServerCommandProcessor(JSession* session,JSocketBase *socket);
	void process(const QByteArray& data);
	EProcessorType getProcessorType()const;
private:
	void processCommand(JID type,JID param);
	void replyCommandResult(JID type,JCode result);
};

#endif // JMAINSERVERCOMMANDPROCESSOR_H
