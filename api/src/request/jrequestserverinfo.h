#ifndef JREQUESTSERVERINFO_H
#define JREQUESTSERVERINFO_H

#include "jinformationrequestbase.h"

#include "../global/jserverinfo.h"

class JRequestServerInfo : public JInformationRequestBase
{
    Q_OBJECT
public:
    explicit JRequestServerInfo(QObject *parent = 0);
	JServerInfo pullServerInfo(JID serverId,int msecs = 30000);
	NetworkData::JHead getHead(JID id)const;
};

#endif // JREQUESTSERVERINFO_H
