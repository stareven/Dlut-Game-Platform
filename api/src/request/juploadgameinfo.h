#ifndef JUPLOADGAMEINFO_H
#define JUPLOADGAMEINFO_H

#include "jinformationsendbase.h"

class JGameInfo;

class JUploadGameInfo : public JInformationSendBase
{
    Q_OBJECT
public:
    explicit JUploadGameInfo(QObject *parent = 0);
	JCode pushGameInfo(const JGameInfo& gameinfo,int msecs=30000);
	NetworkData::JHead getHead(JID id)const;
};

#endif // JUPLOADGAMEINFO_H
