#ifndef JMAINSERVERUSERREGISTERPROCESSOR_H
#define JMAINSERVERUSERREGISTERPROCESSOR_H

#include <Processor/JServerNetworkDataProcessorBase>

class JMainServerUserRegisterProcessor : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JMainServerUserRegisterProcessor(JSession* session,JSocketBase *socket);
	void process(const QByteArray& data);
	EProcessorType getProcessorType()const;

	void replyRegisterResult(JCode result,JID userId,const QString& loginname);
protected:
	virtual void processUserRegister(const QString& loginname,const QString& password);
};

#endif // JMAINSERVERUSERREGISTERPROCESSOR_H
