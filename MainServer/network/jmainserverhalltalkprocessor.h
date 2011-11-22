#ifndef JMAINSERVERHALLTALKPROCESSOR_H
#define JMAINSERVERHALLTALKPROCESSOR_H

#include <Processor/JServerNetworkDataProcessorBase>

class JMainServerHallTalkProcessor : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JMainServerHallTalkProcessor(JSession* session,JSocketBase *socket);
	void process(const QByteArray& data);
	EProcessorType getProcessorType()const;
public slots:
	void sendMessage(const QString& msg);
signals:
	void rcvMessage(const QString& msg);
};

#endif // JMAINSERVERHALLTALKPROCESSOR_H
