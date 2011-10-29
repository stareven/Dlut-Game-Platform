#ifndef JSUBSERVERDB_H
#define JSUBSERVERDB_H

#include "global/jglobal.h"

namespace SubServer
{
	class SSubServer;
}

class JSubServerDb
{
public:
    JSubServerDb();
	virtual bool isControlAble(JID serverId,JID runnerId);
	virtual bool checkBaseInfo(const SubServer::SSubServer&);
};

#endif // JSUBSERVERDB_H
