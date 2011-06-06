#ifndef JSUBSERVERSRV_H
#define JSUBSERVERSRV_H

#include <QList>
//#include "ssubserver.h"
#include <QMap>
#include "jglobal.h"
namespace SubServer
{
	class SGameServerInfo0;
	class SGameFileServerInfo0;
	class SSubServerInfo0;
	class SGameInfo2;
	class SGameInfo1;
	class SGameInfo4;
	class SSubServerInfo1;
	class SGameInfo3;
};
class JVersion;

class JSubServerSrv
{
public:
	JCode addServer(const SubServer::SGameServerInfo0 &);
	JCode addServer(const SubServer::SGameFileServerInfo0 &);
	JCode addServer(const SubServer::SSubServerInfo0 &);
	JCode updateGameInfo(const SubServer::SGameInfo2 &);
	QList<SubServer::SGameInfo1> getAllGameList()const;
	QList<SubServer::SGameInfo1> getAvailableGameList()const;
	SubServer::SGameInfo4 getGameInfo(JID gameid)const;
private:
	static QMap<JID,SubServer::SSubServerInfo1> g_servers;
	static QMap<JID , QMap<JVersion,SubServer::SGameInfo3> > g_games;


//	JCode removeServer(JID id);
//	void getGameNameList()const;
//	void getGameIntro(JID id)const;
};

#endif // JSUBSERVERSRV_H
