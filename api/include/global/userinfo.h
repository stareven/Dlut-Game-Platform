#ifndef USERINFO_H
#define USERINFO_H

#include "jglobal.h"

#include <QString>

namespace UserInfo
{
	struct SUserInfo
	{
		JID m_userId;
		QString m_nickname;
		QString m_organization;
		SUserInfo(JID id=-1,
				  const QString& name="no such user",
				  const QString& org="error");
	};
}

class QDataStream;
QDataStream& operator >> (QDataStream&,UserInfo::SUserInfo&);
QDataStream& operator << (QDataStream&,const UserInfo::SUserInfo&);

#endif // USERINFO_H
