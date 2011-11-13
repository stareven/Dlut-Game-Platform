#ifndef JREQUESTCONTROLROLE_H
#define JREQUESTCONTROLROLE_H

#include "jrequestbase.h"
#include "../global/jglobal.h"
#include "../global/elogin.h"

class JClientControlRoleProcessor;

class JRequestControlRole : public JRequestBase
{
    Q_OBJECT
public:
    explicit JRequestControlRole(QObject *parent = 0);
	void sendControlRole(JID userId,ERole role,EControlRoleAction act);
	enum ESendControlRoleState{
		ESCRS_Init,
		ESCRS_Sending,
		ESCRS_Success,
		ESCRS_Failed,
	};
	ESendControlRoleState getSendControlRoleState()const;
	bool waitForSended(int msecs=30000);
	const QString& getSendError()const;
signals:
	void receiveControlRoleResult(JID userId,JCode result);
public slots:
	void on_processor_receiveControlRoleResult(JID userId,JCode result);
private:
	ESendControlRoleState m_state;
	JCode m_sendError;
	JClientControlRoleProcessor *m_processor;
};

#endif // JREQUESTCONTROLROLE_H
