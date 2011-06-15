#ifndef JSUBSERVERSTARTUP_H
#define JSUBSERVERSTARTUP_H

#include "eportsrv.h"
#include "jglobal.h"
#include "ssubserver.h"



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
};

#endif // JSUBSERVERSTARTUP_H
