#ifndef JMAINSERVERLOGINPROCESSOR_H
#define JMAINSERVERLOGINPROCESSOR_H

#include <Processor/JServerNetworkDataProcessorBase>

class JMainServerLoginProcessor : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JMainServerLoginProcessor(JServerSocketBase *socket);
	void process(const QByteArray& data);
	JType getProcessorType()const;
};

#endif // JMAINSERVERLOGINPROCESSOR_H
