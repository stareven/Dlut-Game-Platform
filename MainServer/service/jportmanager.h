#ifndef JPORTMANAGER_H
#define JPORTMANAGER_H

#include <QtGlobal>

#include "global/eportsrv.h"

template<class T,class U>
class QMap;

class JServerType;

class JPortManager
{
public:
    enum EPortServer{EPS_FREE,EPS_SECRET};
    JPortManager(EPortServer);
    void addSubServerPort(const JServerType&);
    quint16 getSubServerPort(EServerType)const;
private:
    QMap<EServerType,quint16>& m_subServers;
};

#endif // JPORTMANAGER_H
