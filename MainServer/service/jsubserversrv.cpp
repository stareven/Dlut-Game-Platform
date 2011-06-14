#include "jsubserversrv.h"

#include "ssubserver.h"
#include "jversion.h"

#include "database/jsubserverdb.h"
#include "database/jgameinfodb.h"

QMap<JID,SubServer::SSubServer> SubServer::JSubServerData::s_servers;
QMap<JID,SubServer::SGameInfo2> SubServer::JSubServerData::s_games;
QMap< JID,QMap<JVersion,QSet<JID> > > SubServer::JSubServerData::s_relations;

JCode SubServer::JSubServerData::addSubServer(const SubServer::SSubServer& ss)
{
	if(s_servers.contains (ss.m_serverId)) return 3;
	s_servers.insert (ss.m_serverId,ss);
	return 0;
}

JCode SubServer::JSubServerData::updateGameInfo(const SubServer::SGameInfo2& gi)
{
	if(s_games.contains (gi.m_gameId)) return 3;
	s_games.insert (gi.m_gameId,gi);
	return 0;
}

JCode SubServer::JSubServerData::addRelation(JID serverId,JID gameId,const JVersion& gameVersion)
{
	if(s_relations[gameId][gameVersion].contains (serverId)) return 3;
	s_relations[gameId][gameVersion].insert (serverId);
	return 0;
}

QList<SubServer::SGameInfo2> SubServer::JSubServerData::getGameList()const
{
	return s_games.values ();
}

QMap<JVersion,QSet<JID> > SubServer::JSubServerData::getServersByGameid(JID gameId)const
{
	return s_relations.value (gameId);
}

QSet<JID> SubServer::JSubServerData::getServers(JID gameId,JVersion version)const
{
	return s_relations.value(gameId).value(version);
}

SubServer::JSubServerData::JSubServerData()
{
}

////////////////////////////////////////////////////////////////////

JCode SubServer::JSubServerSrv::addSubServer(const SubServer::SSubServer &server)
{
	JSubServerDb db;
	if(!db.isControlAble (server.m_serverId,m_runner)) return 1;
	if(!db.checkBaseInfo (server)) return 2;
	return m_data.addSubServer (server);
}

JCode SubServer::JSubServerSrv::updateGameInfo(const SubServer::SGameInfo2 &gi)
{
	JGameInfoDb db;
	if(!db.isWritable (gi.m_gameId,m_runner)) return 1;
	if(!db.checkBaseInfo (gi)) return 2;
	return m_data.updateGameInfo (gi);
}

JCode SubServer::JSubServerSrv::addRelation(JID serverId,JID gameId,const JVersion& gameVersion)
{
	JSubServerDb sdb;
	JGameInfoDb gdb;
	if(!gdb.isWritable (gameId,m_runner)
		|| !sdb.isControlAble (serverId,m_runner))
		return 1;
	return m_data.addRelation (serverId,gameId,gameVersion);
}

SubServer::JSubServerSrv::JSubServerSrv(JID runner)
{
	m_runner=runner;
}

////////////////////////////////////////////////////////////////////

QList<SubServer::SGameInfo2> SubServer::JGameInfoSrv::getGameList()const
{
	return m_data.getGameList ();
}

QMap<JVersion,QSet<JID> > SubServer::JGameInfoSrv::getServersByGameid(JID gameid)const
{
	return m_data.getServersByGameid (gameid);
}

QSet<JID> SubServer::JGameInfoSrv::getServers(JID gameId,JVersion version)const
{
	return m_data.getServers(gameId,version);
}
