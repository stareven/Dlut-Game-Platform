#include "global/userinfo.h"

#include <QDataStream>

UserInfo::SUserInfo::SUserInfo(JID id,
		  const QString& name,
		  const QString& org)
{
	m_userId=id;
	m_nickname=name;
	m_organization=org;
}

QDataStream& operator >> (QDataStream& stream,UserInfo::SUserInfo& ui)
{
	stream>>ui.m_userId;
	stream>>ui.m_nickname;
	stream>>ui.m_organization;
	return stream;
}

QDataStream& operator << (QDataStream& stream,const UserInfo::SUserInfo& ui)
{
	stream<<ui.m_userId;
	stream<<ui.m_nickname;
	stream<<ui.m_organization;
	return stream;
}
