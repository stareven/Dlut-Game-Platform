#ifndef JGAMEINFOSRV_H
#define JGAMEINFOSRV_H

#include <QList>
#include "jglobal.h"
#include "sgame.h"

namespace JGameInfoSrv
{
    class JGis4Player
    {
    public:
	QList<JID> getIdList()const;
	QList<SGameName> getNameList()const;
	SGameInfo getInfoById(JID id)const;
    };
    class JGis4Admin
    {
    public:
	JCode addGame(const SGameInfo&)const;
	JCode deleteGame(JID id)const;
    };
}
#endif // JGAMEINFOSRV_H
