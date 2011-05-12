#include "jportservice.h"

#include <QMap>

#include "network/jserverbase.h"

static QMap< JPortService::EPortServer ,QMap<EServerType,quint16> > g_ServerMap;

JPortService::JPortService(EPortServer server)
    :m_subServers(g_ServerMap[server])
{
}

void JPortService::addSubServerPort(const JServerBase& server)
{
    m_subServers.insert(server.serverType(),server.serverPort());
}

quint16 JPortService::getSubServerPort(EServerType type)const
{
    return m_subServers.value(type,0);
}
