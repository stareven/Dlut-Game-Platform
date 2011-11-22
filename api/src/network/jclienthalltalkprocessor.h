#ifndef JCLIENTHALLTALKPROCESSOR_H
#define JCLIENTHALLTALKPROCESSOR_H

#include "jclientnetworkdataprocessorbase.h"

class JClientHallTalkProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
	explicit JClientHallTalkProcessor(JSession* session,JSocketBase *socket);
public:
	static JClientHallTalkProcessor* getInstance();
	void sendMessage(const QString& msg);
signals:
	void rcvMessage(const QString& msg);
protected:
	void process(const QByteArray& data);
	EProcessorType getProcessorType()const;
};

#endif // JCLIENTHALLTALKPROCESSOR_H
