#ifndef JMAINSERVERCONTROLROLEPROCESSOR_H
#define JMAINSERVERCONTROLROLEPROCESSOR_H

#include <Processor/JServerNetworkDataProcessorBase>
#include <Global/Login>

class JMainServerControlRoleProcessor : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JMainServerControlRoleProcessor(JSession* session,JSocketBase *socket);
	void process(const QByteArray& data);
	EProcessorType getProcessorType()const;
private:
	void processControlRole(JID userId,ERole role,EControlRoleAction act);
	void replyResult(JID userId,JCode result);
};

#endif // JMAINSERVERCONTROLROLEPROCESSOR_H
