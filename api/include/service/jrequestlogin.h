#ifndef JREQUESTLOGIN_H
#define JREQUESTLOGIN_H

#include "jrequestbase.h"
#include "global/elogin.h"

#include "clientapi_global.h"

class JRequestLoginSocket;

class CLIENTAPISHARED_EXPORT JRequestLogin : public JRequestBase
{
    Q_OBJECT
public:
	explicit JRequestLogin(QObject *parent = 0);
    void login(const QString& loginname,
               const QString& passwd,
               const JID& role);
	enum ELoginState{
		ELS_Init,
		ELS_Sending,
		ELS_Success,
		ELS_Failed,
    };
	ELoginState getLoginState()const;
    bool waitForLogined(int msecs=30000);
	const QString& getLoginError()const;
signals:
	void loginResult(bool);
protected slots:
	void on_socket_loginCode(JCode);
private:
	ELoginState m_state;
	ELogin m_loginError;
	JRequestLoginSocket *m_socket;
};

#endif // JREQUESTLOGIN_H
