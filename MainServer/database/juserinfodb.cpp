#include "juserinfodb.h"

#include <QMap>

static const UserInfo::SUserInfo users[]={
	{109,"elephant liu","JDMD studio"},
	{241,"JDMD studio","CPF"},
	{794,"li xiao pang","CPF"},
	{900,"sample player","JDMD studio"},
	{901,"sampledesigner","123"},
	{902,"sampleserverrunner","123"},
	{903,"sampleadmin","123"},
	{904,"sampleroot","123"}
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
		static const UserInfo::SUserInfo userinfo(-1,"no such user","error");
		return userinfo;

	}
}
