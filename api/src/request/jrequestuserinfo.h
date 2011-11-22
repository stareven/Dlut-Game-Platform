#ifndef JREQUESTUSERINFO_H
#define JREQUESTUSERINFO_H

#include "jinformationrequestbase.h"

#include "../global/juserinfo.h"

class JRequestUserInfo : public JInformationRequestBase
{
    Q_OBJECT
public:
    explicit JRequestUserInfo(QObject *parent = 0);
	JUserInfo pullUserInfo(JID userId,int msecs = 30000);
	JUserInfo getUserInfo(JID userId);
	NetworkData::JHead getHeadById(JID id)const;
};

#endif // JREQUESTUSERINFO_H
