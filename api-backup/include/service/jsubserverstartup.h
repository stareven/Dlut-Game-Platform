#ifndef JSUBSERVERSTARTUP_H
#define JSUBSERVERSTARTUP_H

#include "global/eportsrv.h"
#include "global/jglobal.h"
#include "global/ssubserver.h"

#include "subserverapi_global.h"

class JRequestPort;
class JRequestLogin;
class JSendGsInfo;

class SUBSERVERAPISHARED_EXPORT JSubServerStartup
{
public:
	SHost m_host;///< MainServer的端口及地址
	QString m_loginname;///< 登录名
	QString m_passwd;///< 登录密码
	JID m_role;///< 登录身份。若想发送SubServer相关信息，需要以ROLE_GAMESERVERRUNNER身份登录。
	SubServer::SGameInfo2 m_gameinfo;///< 相关游戏信息。
	SubServer::SSubServer m_serverinfo;///< SubServer信息。

    JSubServerStartup();
	~JSubServerStartup();
	enum EReturnValue{
		ERV_Success,
		ERV_ConnectFailed,
		ERV_LoginFailed,
		ERV_PlhFailed,
		ERV_SendFailed,
	};
	EReturnValue startup()const;
private:
	JRequestPort* m_ps;
	JRequestLogin* m_login;
	JSendGsInfo* m_gis;
};

#endif // JSUBSERVERSTARTUP_H
