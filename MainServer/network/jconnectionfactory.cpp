#include "jconnectionfactory.h"

#include "network/jconnectionbase.h"
#include "jloginconnection.h"
#include "jgameinfoconnection.h"
#include "jportconnection.h"
#include "jsubserverconnection.h"

JConnectionFactory::JConnectionFactory()
{
}

JConnectionBase* JConnectionFactory::createConnection(EServerType st,QTcpSocket* socket,QObject* parent)
{
    switch(st)
    {
    case EST_LOGIN:
		return new JLoginConnection(socket,parent);
	break;
    case EST_GAMEINFO:
        return new JGameInfoConnection(socket,parent);
    case EST_FREEPORT:
        return new JPortConnection(JPortManager::EPS_FREE,socket,parent);
    case EST_SECRETPORT:
        return new JPortConnection(JPortManager::EPS_SECRET,socket,parent);
	case EST_SUBSERVER:
		return new JSubServerConnection(socket,parent);
    case EST_MAX:
	return new JConnectionBase(socket,parent);
    }
    return new JConnectionBase(socket,parent);
}
