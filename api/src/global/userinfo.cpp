#include "global/userinfo.h"

#include <QDataStream>

/*!
	\namespace UserInfo
	\brief 玩家信息相关。
*/

/*
	\class SUserInfo
	\brief 记录一名玩家的信息。

	包括玩家的Id，昵称和组织名。
*/

/*!
	构造一个SUserInfo。Id为\a id ，昵称为\a name ，组织名\a org 。
*/
UserInfo::SUserInfo::SUserInfo(JID id,
		  const QString& name,
		  const QString& org)
{
	m_userId=id;
	m_nickname=name;
	m_organization=org;
}

/*!
	\relates UserInfo::SUserInfo
	从流\a stream 中读入到\a ui 中。
*/
QDataStream& operator >> (QDataStream& stream,UserInfo::SUserInfo& ui)
{
	stream>>ui.m_userId;
	stream>>ui.m_nickname;
	stream>>ui.m_organization;
	return stream;
}

/*!
	\relates UserInfo::SUserInfo
	将\a ui 中写入到流\a stream 中。
*/
QDataStream& operator << (QDataStream& stream,const UserInfo::SUserInfo& ui)
{
	stream<<ui.m_userId;
	stream<<ui.m_nickname;
	stream<<ui.m_organization;
	return stream;
}
