#include "jgameinfodb.h"

#include <QMap>
#include <QSet>
#include <QFile>
#include <QTextStream>

#include "global/ssubserver.h"

static QMap<JID,QSet<JID > > s_game_runner;

struct SGameInfoCheck{
	JID m_gameId;
	QString m_name;
	JID m_authour;
};
static QMap<JID,SGameInfoCheck> s_gameinfo;

JGameInfoDb::JGameInfoDb()
{
	static bool first=true;
	if(first)
	{
		first=false;
		{
			QFile file("../database/game_runner");
			file.open(QIODevice::ReadOnly);
			QTextStream stream(&file);
			for(int i=0;i<1000;++i)
			{
				if(stream.atEnd()) break;
				JID gameId,runnerId;
				stream>>gameId>>runnerId;
				s_game_runner[gameId].insert(runnerId);
			}
		}
		{
			QFile file("../database/game_info");
			file.open(QIODevice::ReadOnly);
			QTextStream stream(&file);
			for(int i=0;i<1000;++i)
			{
				if(stream.atEnd()) break;
				SGameInfoCheck gic;
				stream>>gic.m_gameId>>gic.m_name>>gic.m_authour;
				s_gameinfo.insert(gic.m_gameId,gic);
			}
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

