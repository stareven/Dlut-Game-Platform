#ifndef USERINFO_H
#define USERINFO_H

#include "jglobal.h"

#include <QString>

namespace UserInfo
{
	struct SUserInfo
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
QDataStream& operator >> (QDataStream&,UserInfo::SUserInfo&);
QDataStream& operator << (QDataStream&,const UserInfo::SUserInfo&);

#endif // USERINFO_H
