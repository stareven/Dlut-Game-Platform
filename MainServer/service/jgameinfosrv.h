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
    private:
        enum{ GameidMin=256,GameidMax=65535 };
    public:
        // 0 succeed
        // 1 game name duplicate
        // 2 game id full
        JCode addGame(SGameInfo&)const;

        // 0 succeed
        // 1 nothing to delete
	JCode deleteGame(JID id)const;
    };
}
#endif // JGAMEINFOSRV_H
