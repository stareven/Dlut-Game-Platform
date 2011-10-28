#include "global/userinfo.h"

#include <QDataStream>

/*!
	\namespace UserInfo
	\ingroup global
	\brief 玩家信息相关。
*/

/*!
	\class UserInfo::SUserInfo userinfo.h "global/userinfo.h"
	\brief 记录一名玩家的信息。

	包括玩家的Id，昵称和组织名。
*/

/*!
	\brief 构造一个SUserInfo。
	
	Id为\a id ，昵称为\a name ，组织名\a org 。
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
	\brief 从流\a stream 中读入到\a ui 中。
	
	格式： <JID:userId> <QString:nickname> <QString:organization>
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
	\brief 将\a ui 中写入到流\a stream 中。
	
	格式参见 operator>>(QDataStream& stream,UserInfo::SUserInfo& ui)
*/
QDataStream& operator << (QDataStream& stream,const UserInfo::SUserInfo& ui)
{
	stream<<ui.m_userId;
	stream<<ui.m_nickname;
	stream<<ui.m_organization;
	return stream;
}
