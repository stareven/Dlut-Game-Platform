#include "jgameinfodb.h"

#include <QMap>
#include <QSet>

#include "ssubserver.h"

static QMap<JID,QSet<JID > > s_game_runner;

struct SGameInfoCheck{
	JID m_gameId;
	QString m_name;
	JID m_authour;
};
static QMap<JID,SGameInfoCheck> s_gameinfo;

JGameInfoDb::JGameInfoDb()
{
	//runner id : 902 : sampleserverrunner
	//game id : 53379 : sample
	if(s_game_runner.isEmpty ())
	{
		s_game_runner[109].insert (902);
	}
	if(s_gameinfo.isEmpty ())
	{
		SGameInfoCheck gis[]={
			{109,"sample server",901/*sampledesigner*/},
		};
		int NUM_GAME=sizeof(gis)/sizeof(SGameInfoCheck);
		for(int i=0;i<NUM_GAME;++i)
		{
			s_gameinfo.insert (gis[i].m_gameId,gis[i]);
		}
	}
}

bool JGameInfoDb::isWritable(JID gameId,JID runnerId)
{
	const QMap<JID,QSet<JID> > &sgr=s_game_runner;
	if(!sgr.contains (gameId)) return false;
	return sgr[gameId].contains (runnerId) ;
}



bool JGameInfoDb::checkBaseInfo(const SubServer::SGameInfo2& gi)
{
	if(!s_gameinfo.contains (gi.m_gameId)) return false;
	const SGameInfoCheck &giq=s_gameinfo.value (gi.m_gameId);
	if(giq.m_gameId!=gi.m_gameId) return false;
	if(giq.m_name!=gi.m_name) return false;
	if(giq.m_authour!=gi.m_author) return false;
	return true;
}

