#include "juserinfodb.h"

#include <QMap>

static const UserInfo::SUserInfo users[]={
	UserInfo::SUserInfo(109,"elephant liu","JDMD studio"),
	UserInfo::SUserInfo(241,"JDMD studio","CPF"),
	UserInfo::SUserInfo(794,"li xiao pang","CPF"),
	UserInfo::SUserInfo(900,"sample player","sample.org"),
	UserInfo::SUserInfo(901,"sample designer","sample.org"),
	UserInfo::SUserInfo(902,"sample serverrunner","sample.org"),
	UserInfo::SUserInfo(903,"sample admin","sample.org"),
	UserInfo::SUserInfo(904,"sample root","sample.org"),
	UserInfo::SUserInfo(1001,"debug A","debug.org"),
	UserInfo::SUserInfo(1002,"debug B","debug.org"),
	UserInfo::SUserInfo(1003,"debug C","debug.org"),
	UserInfo::SUserInfo(1004,"debug D","debug.org"),
	UserInfo::SUserInfo(1005,"debug E","debug.org"),
	UserInfo::SUserInfo(1006,"debug F","debug.org"),
};

static QMap<JID,UserInfo::SUserInfo> s_users;

JUserInfoDb::JUserInfoDb()
{
	if(s_users.isEmpty())
	{
		const int n=sizeof(users)/sizeof(UserInfo::SUserInfo);
		for(int i=0;i<n;++i)
		{
			s_users.insert(users[i].m_userId,users[i]);
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
