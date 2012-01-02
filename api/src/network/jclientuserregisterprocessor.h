#ifndef JCLIENTUSERREGISTERPROCESSOR_H
#define JCLIENTUSERREGISTERPROCESSOR_H

#include "jclientnetworkdataprocessorbase.h"
#include "../global/elogin.h"

class JClientUserRegisterProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
	explicit JClientUserRegisterProcessor(JSession* session,JSocketBase *socket);
public:
	static JClientUserRegisterProcessor* getInstance();
	void sendRegister(const QString& loginname,const QString& password,ERole role);
signals:
	void receiveRegisterResult(JCode result,JID userId,const QString& loginname);
protected:
	void process(const QByteArray &data);
    JType getProcessorType()const;
};

#endif // JCLIENTUSERREGISTERPROCESSOR_H
