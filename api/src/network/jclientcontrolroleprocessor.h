#ifndef JCLIENTCONTROLROLEPROCESSOR_H
#define JCLIENTCONTROLROLEPROCESSOR_H

#include "jclientnetworkdataprocessorbase.h"
#include "../global/elogin.h"

class JClientControlRoleProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
	explicit JClientControlRoleProcessor(JSession* session,JSocketBase *socket);
public:
	static JClientControlRoleProcessor* getInstance();

	void sendControlRole(JID userId,ERole role,EControlRoleAction act);
signals:
	void receiveControlRoleResult(JID userId,JCode result);
protected:
	void process(const QByteArray& data);
	EProcessorType getProcessorType()const;
};

#endif // JCLIENTCONTROLROLEPROCESSOR_H
