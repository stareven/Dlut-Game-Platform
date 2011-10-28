#ifndef JUPLOADSERVERINFO_H
#define JUPLOADSERVERINFO_H

#include "jinformationsendbase.h"

class JServerInfo;

class JUploadServerInfo : public JInformationSendBase
{
    Q_OBJECT
public:
    explicit JUploadServerInfo(QObject *parent = 0);
	JCode pushServerInfo(const JServerInfo& serverinfo,int msecs=30000);
	NetworkData::JHead getHead(JID id)const;
};

#endif // JUPLOADSERVERINFO_H
