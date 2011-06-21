#include "jsubserversrv.h"

#include "global/ssubserver.h"
#include "global/jversion.h"

#include "database/jsubserverdb.h"
#include "database/jgameinfodb.h"

QMap<JID,SubServer::SSubServer> SubServer::JSubServerData::s_servers;
QMap<JID,SubServer::SGameInfo2> SubServer::JSubServerData::s_games;
QMap< JID,QMap<JVersion,QSet<JID> > > SubServer::JSubServerData::s_relations;

JCode SubServer::JSubServerData::addSubServer(const SubServer::SSubServer& ss)
{
	if(s_servers.contains (ss.m_serverId)) return 3;
	s_servers.insert (ss.m_serverId,ss);
	qDebug()<<"addSubServer:"<<s_servers.keys();
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

JCode SubServer::JSubServerData::deleteSubServer(JID serverId)
{
	qDebug()<<"deleteSubServer:"<<serverId;
	s_servers.remove(serverId);
	return 0;
}

QList<SubServer::SGameInfo2> SubServer::JSubServerData::getGameList()const
{
	return s_games.values ();
}

//QMap<JVersion,QSet<JID> > SubServer::JSubServerData::getServersByGameid(JID gameId)const
//{
//	return s_relations.value (gameId);
//}

QSet<JID> SubServer::JSubServerData::getServers(JID gameId,JVersion version)const
{
	qDebug()<<s_servers.keys();
	foreach(JID serverId,s_relations[gameId][version])
	{
		if(!s_servers.contains(serverId))
		{
			qDebug()<<gameId<<version.getData()<<serverId;
			s_relations[gameId][version].remove(serverId);
		}
	}

	return s_relations.value(gameId).value(version);
}

SubServer::SSubServer SubServer::JSubServerData::getServerInfo(JID serverId)const
{
	return s_servers.value(serverId);
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

	if( ( SubServer::SSubServer::ET_GameServer == server.m_type && server.m_serverId%2 == 0)
		|| ( SubServer::SSubServer::ET_GameFileServer == server.m_type && server.m_serverId%2 == 1) )
		return 4;
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
	if(!gdb.isWritable (gameId,m_runner))
	{
		qDebug()<<"runner"<<m_runner<<"can not write game"<<gameId;
		return 1;
	}
	if(!sdb.isControlAble (serverId,m_runner))
	{
		qDebug()<<"runner"<<m_runner<<"can not control server"<<serverId;
		return 1;
	}
	return m_data.addRelation (serverId,gameId,gameVersion);
}

JCode SubServer::JSubServerSrv::deleteSubServer(JID serverId)
{
	JSubServerDb sdb;
	if(!sdb.isControlAble(serverId,m_runner))
	{
		return 1;
	}
	return m_data.deleteSubServer(serverId);
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

//QMap<JVersion,QSet<JID> > SubServer::JGameInfoSrv::getServersByGameid(JID gameid)const
//{
//	return m_data.getServersByGameid (gameid);
//}

QSet<JID> SubServer::JGameInfoSrv::getServers(JID gameId,JVersion version)const
{
	return m_data.getServers(gameId,version);
}

SubServer::SSubServer SubServer::JGameInfoSrv::getServerInfo(JID serverId)const
{
	return m_data.getServerInfo(serverId);
}
