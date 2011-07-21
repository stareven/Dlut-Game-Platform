#include "juserinfodb.h"

#include <QMap>
#include <QFile>
#include <QTextStream>

//static const UserInfo::SUserInfo users[]={
//	UserInfo::SUserInfo(109,"elephant liu","JDMD studio"),
//	UserInfo::SUserInfo(241,"JDMD studio","CPF"),
//	UserInfo::SUserInfo(794,"li xiao pang","CPF"),
//	UserInfo::SUserInfo(900,"sample player","sample.org"),
//	UserInfo::SUserInfo(901,"sample designer","sample.org"),
//	UserInfo::SUserInfo(902,"sample serverrunner","sample.org"),
//	UserInfo::SUserInfo(903,"sample admin","sample.org"),
//	UserInfo::SUserInfo(904,"sample root","sample.org"),
//	UserInfo::SUserInfo(1001,"debug A","debug.org"),
//	UserInfo::SUserInfo(1002,"debug B","debug.org"),
//	UserInfo::SUserInfo(1003,"debug C","debug.org"),
//	UserInfo::SUserInfo(1004,"debug D","debug.org"),
//	UserInfo::SUserInfo(1005,"debug E","debug.org"),
//	UserInfo::SUserInfo(1006,"debug F","debug.org"),
//};

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
