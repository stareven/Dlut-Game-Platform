#ifndef JUPLOADUSERINFO_H
#define JUPLOADUSERINFO_H

#include "jinformationsendbase.h"

class JUserInfo;

class JUploadUserInfo : public JInformationSendBase
{
    Q_OBJECT
public:
    explicit JUploadUserInfo(QObject *parent = 0);
	JCode pushUserInfo(const JUserInfo& userinfo,int msecs=30000);
	NetworkData::JHead getHead(JID id)const;
};

#endif // JUPLOADUSERINFO_H
