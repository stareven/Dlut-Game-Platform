#ifndef JSUBSERVERSTARTUP_H
#define JSUBSERVERSTARTUP_H

#include "global/eportsrv.h"
#include "global/jglobal.h"
#include "global/ssubserver.h"

class JRequestPort;
class JRequestLogin;
class JSendGsInfo;

class JSubServerStartup
{
public:
	SHost m_host;
	QString m_loginname;
	QString m_passwd;
	JID m_role;
	SubServer::SGameInfo2 m_gameinfo;
	SubServer::SSubServer m_serverinfo;

    JSubServerStartup();
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
