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
	class SSubServer;
};
class JVersion;

namespace SubServer
{
	class JSubServerSrv;
	class JGameInfoSrv;

	class JSubServerData
	{
	public:
		JCode addSubServer(const SSubServer&);
		JCode updateGameInfo(const SGameInfo2&);
		JCode addRelation(JID serverId,JID gameId,const JVersion& gameVersion);
		QList<SGameInfo2> getGameList()const;
		QMap<JVersion,QSet<JID> > getServersByGameid(JID gameid)const;
	private:
		JSubServerData();
		static QMap<JID,SSubServer> s_servers;
		static QMap<JID,SGameInfo2> s_games;
		static QMap< JID,QMap<JVersion,QSet<JID> > > s_relations;

		friend class JSubServerSrv;
		friend class JGameInfoSrv;
	};

	class JSubServerSrv
	{
	public:
		JCode addSubServer(const SSubServer&);
		JCode updateGameInfo(const SGameInfo2&);
		JCode addRelation(JID serverId,JID gameId,const JVersion& gameVersion);

		JSubServerSrv();
		void setRunner(JID);
	private:
		JSubServerData m_data;
		JID m_runner;
	};

	class JGameInfoSrv
	{
	public:
		QList<SGameInfo2> getGameList()const;
		QMap<JVersion,QSet<JID> > getServersByGameid(JID gameid)const;
	private:
		JSubServerData m_data;
	};


}

#endif // JSUBSERVERSRV_H
