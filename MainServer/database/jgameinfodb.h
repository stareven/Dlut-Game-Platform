#ifndef JGAMEINFODB_H
#define JGAMEINFODB_H

#include "jglobal.h"

namespace SubServer
{
	class SGameInfo2;
}

class JGameInfoDb
{
public:
    JGameInfoDb();
	virtual bool isWritable(JID gameId,JID runnerId);
	virtual bool checkBaseInfo(const SubServer::SGameInfo2&);
};

#endif // JGAMEINFODB_H
