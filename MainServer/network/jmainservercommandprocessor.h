#ifndef JMAINSERVERCOMMANDPROCESSOR_H
#define JMAINSERVERCOMMANDPROCESSOR_H

#include <Processor/JServerNetworkDataProcessorBase>

class JMainServerSocket;

class JMainServerCommandProcessor : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JMainServerCommandProcessor(JMainServerSocket *socket);
	void process(const QByteArray& data);
	JType getProcessorType()const;
};

#endif // JMAINSERVERCOMMANDPROCESSOR_H
