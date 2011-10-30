#include "jtextstreamuserinfodb.h"

#include <QMap>
#include <QFile>
#include <QTextStream>

static QMap<JID,JUserInfo> s_users;

JTextStreamUserInfoDB::JTextStreamUserInfoDB(QObject* parent)
	:JAbstractUserInfoDB(parent)
{
	if(s_users.isEmpty())
	{
		QFile file("../database/userinfo");
		file.open(QIODevice::ReadOnly | QIODevice::Text);
		QTextStream stream(&file);
		for(int i=0;i<1000;++i)
		{
			if(stream.atEnd()) break;
			JID userId;
			QString nickname,organization;
			stream>>userId;
			stream>>nickname;
			stream>>organization;
			JUserInfo userinfo(userId,nickname,organization);
			s_users.insert(userinfo.getUserId(),userinfo);
		}
	}
}

JUserInfo JTextStreamUserInfoDB::getUserInfoById(JID userId)
{
	return s_users.value(userId,JUserInfo(userId,
										  "no such user on server database",
										  "no such user on server database"
										 ));
}

JCode JTextStreamUserInfoDB::updateUserInfo(const JUserInfo& userinfo)
{
	s_users.insert(userinfo.getUserId(),userinfo);
	return 0;
}

void JTextStreamUserInfoDB::flush()
{
	if(s_users.isEmpty()) return;
	QFile file("../database/userinfo");
	file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
	QTextStream stream(&file);
	foreach(JUserInfo userinfo,s_users){
		stream<<userinfo.getUserId();
		stream<<userinfo.getNickname();
		stream<<userinfo.getOrganization();
		stream<<endl;
	}
	s_users.clear();
}
