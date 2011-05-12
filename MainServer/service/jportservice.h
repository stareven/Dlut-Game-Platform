#ifndef JPORTSERVICE_H
#define JPORTSERVICE_H

#include <QtGlobal>

#include "network/jconnectionfactory.h"

template<class T,class U>
class QMap;

class JServerBase;

class JPortService
{
public:
    enum EPortServer{EPS_FREE,EPS_SECRET};
    JPortService(EPortServer);
    void addSubServerPort(const JServerBase&);
    quint16 getSubServerPort(EServerType)const;
private:
    QMap<EServerType,quint16>& m_subServers;
};

#endif // JPORTSERVICE_H
