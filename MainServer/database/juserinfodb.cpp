#include "juserinfodb.h"

#include <QMap>
#include <QFile>
#include <QTextStream>

static QMap<JID,UserInfo::SUserInfo> s_users;

JUserInfoDb::JUserInfoDb()
{
	static bool first=true;
	if(first)
	{
		first=false;
		QFile file("../database/userinfo");
		file.open(QIODevice::ReadOnly);
		QTextStream stream(&file);
		for(int i=0;i<1000;++i)
		{
			if(stream.atEnd()) break;
			UserInfo::SUserInfo user;
			stream>>user.m_userId;
			stream>>user.m_nickname;
			stream>>user.m_organization;
			s_users.insert(user.m_userId,user);
		}
	}
}

UserInfo::SUserInfo JUserInfoDb::getUserInfo(JID userId)const
{
	if(s_users.contains(userId))
	{
		return s_users.value(userId);
	}else{
		UserInfo::SUserInfo userinfo(userId,"no such user on server database","no such user on server database");
		return userinfo;
	}
}
