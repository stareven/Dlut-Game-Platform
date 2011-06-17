#ifndef JSUBSERVERSTARTUP_H
#define JSUBSERVERSTARTUP_H

#include "global/eportsrv.h"
#include "global/jglobal.h"
#include "global/ssubserver.h"

class JPortService;
class JLoginService2;
class JGsInfoService;

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
	enum ERuturnValue{
		ERV_Success,
		ERV_ConnectFailed,
		ERV_LoginFailed,
		ERV_PlhFailed,
		ERV_SendFailed,
	};
	ERuturnValue startup()const;
private:
	JPortService* m_ps;
	JLoginService2* m_login;
	JGsInfoService* m_gis;
};

#endif // JSUBSERVERSTARTUP_H
