#ifndef JUSERINFODB_H
#define JUSERINFODB_H

#include "global/userinfo.h"

class JUserInfoDb
{
public:
    JUserInfoDb();
	UserInfo::SUserInfo getUserInfo(JID userId)const;
};

#endif // JUSERINFODB_H
