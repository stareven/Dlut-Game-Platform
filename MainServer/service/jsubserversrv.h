#ifndef JSUBSERVERSRV_H
#define JSUBSERVERSRV_H

#include <QList>
#include "ssubserver.h"

class JSubServerSrv
{
public:
	JCode addServer(const SubServer::SGameServerInfo0&);
	JCode addServer(const SubServer::SGameFileServerInfo0 &);
	QList<SubServer::SGameInfo1> getAllGameList()const;
	QList<SubServer::SGameInfo1> getAvailableGameList()const;
	SubServer::SGameInfo4 getGameInfo(JID gameid)const;

//	JCode removeServer(JID id);
//	void getGameNameList()const;
//	void getGameIntro(JID id)const;
};

#endif // JSUBSERVERSRV_H
