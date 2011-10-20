#ifndef JREQUESTGAMEINFO_H
#define JREQUESTGAMEINFO_H

#include "jinformationrequestbase.h"

#include "../global/jgameinfo.h"

class JRequestGameInfo : public JInformationRequestBase
{
    Q_OBJECT
public:
    explicit JRequestGameInfo(QObject *parent = 0);
	JGameInfo pullGameInfo(JID gameId,int msecs = 30000);
	NetworkData::JHead getHead(JID id) const;
};

#endif // JREQUESTGAMEINFO_H
