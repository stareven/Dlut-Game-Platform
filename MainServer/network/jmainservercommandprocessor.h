#ifndef JMAINSERVERCOMMANDPROCESSOR_H
#define JMAINSERVERCOMMANDPROCESSOR_H

#include <Processor/JServerNetworkDataProcessorBase>

class JMainServerCommandProcessor : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JMainServerCommandProcessor(JServerSocketBase *socket);
	void process(const QByteArray& data);
	JType getProcessorType()const;
};

#endif // JMAINSERVERCOMMANDPROCESSOR_H
