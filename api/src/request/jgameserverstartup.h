#ifndef JGAMESERVERSTARTUP_H
#define JGAMESERVERSTARTUP_H

#include "../global/shost.h"
#include "../global/jgameinfo.h"
#include "../global/jserverinfo.h"
#include "../global/elogin.h"

class JGameServerStartup
{
public:
	SHost m_mainserver;
	QString m_loginname;
	QString m_passwd;
	ERole m_role;
	JGameInfo m_gameinfo;
	JServerInfo m_serverinfo;

	enum EReturnValue{
		ERV_Success,
		ERV_ConnectFailed,
		ERV_LoginFailed,
		ERV_PlhFailed,
		ERV_SendFailed,
	};
	EReturnValue startup()const;
    JGameServerStartup();
};

#endif // JGAMESERVERSTARTUP_H
