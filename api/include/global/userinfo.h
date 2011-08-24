#ifndef USERINFO_H
#define USERINFO_H

#include "jglobal.h"
#include "globalapi_global.h"

#include <QString>

/*!
	\file userinfo.h
	\brief 定义了 UserInfo 命名空间。
*/

namespace UserInfo
{
	struct GLOBALAPISHARED_EXPORT SUserInfo
	{
		JID m_userId; /**< 用户ID */
		QString m_nickname; /**< 用户昵称 */
		QString m_organization; /**< 用户组织 */
		SUserInfo(JID id=-1,
				  const QString& name="no such user",
				  const QString& org="error");
	};
}

class QDataStream;
GLOBALAPISHARED_EXPORT QDataStream& operator >> (QDataStream&,UserInfo::SUserInfo&);
GLOBALAPISHARED_EXPORT QDataStream& operator << (QDataStream&,const UserInfo::SUserInfo&);

#endif // USERINFO_H
