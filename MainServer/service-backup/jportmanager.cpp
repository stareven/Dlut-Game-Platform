#include "jportmanager.h"

#include <QMap>

#include "network/jservertype.h"

static QMap< JPortManager::EPortServer ,QMap<EServerType,quint16> > g_ServerMap;

JPortManager::JPortManager(EPortServer server)
    :m_subServers(g_ServerMap[server])
{
}

void JPortManager::addSubServerPort(const JServerType& server)
{
    m_subServers.insert(server.serverType(),server.serverPort());
}

quint16 JPortManager::getSubServerPort(EServerType type)const
{
    return m_subServers.value(type,0);
}
