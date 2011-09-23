#ifndef JREQUESTLOGIN_H
#define JREQUESTLOGIN_H

#include "jrequestbase.h"
#include "../global/elogin.h"

class JClientLoginProcessor;

class JRequestLogin : public JRequestBase
{
    Q_OBJECT
public:
	explicit JRequestLogin(QObject *parent = 0);
    void login(const QString& loginname,
               const QString& passwd,
               const JID& role);
	/// \brief 登录状态           
	enum ELoginState{
		ELS_Init, ///< 初始状态
		ELS_Sending, ///< 正在发送登录请求
		ELS_Success, ///< 登录成功
		ELS_Failed, ///< 登录失败
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
    JClientLoginProcessor *m_processor;
};

#endif // JREQUESTLOGIN_H
