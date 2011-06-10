#include "jsubserversrv.h"

#include "ssubserver.h"

JCode SubServer::JSubServerData::addSubServer(const SSubServer&)
{
	a;
}

JCode SubServer::JSubServerData::updateGameInfo(const SGameInfo2&)
{
	a;
}

JCode SubServer::JSubServerData::addRelation(JID serverId,JID gameId,const JVersion& gameVersion)
{
	a;
}

QList<SubServer::SGameInfo2> SubServer::JSubServerData::getGameList()const
{
	a;
}

QMap<JVersion,QSet<JID> > SubServer::JSubServerData::getServersByGameid(JID gameid)const
{
	a;
}

SubServer::JSubServerData::JSubServerData()
{
}

JCode SubServer::JSubServerSrv::addSubServer(const SubServer::SSubServer &server)
{
	return m_data.addSubServer (server);
}

JCode SubServer::JSubServerSrv::updateGameInfo(const SubServer::SGameInfo2 &gi)
{
	return m_data.updateGameInfo (gi);
}

JCode SubServer::JSubServerSrv::addRelation(JID serverId,JID gameId,const JVersion& gameVersion)
{
	return m_data.addRelation (serverId,gameId,gameVersion);
}

QList<SubServer::SGameInfo2> SubServer::JGameInfoSrv::getGameList()const
{
	return m_data.getGameList ();
}

QMap<JVersion,QSet<JID> > SubServer::JGameInfoSrv::getServersByGameid(JID gameid)const
{
	return m_data.getServersByGameid (gameid);
}
