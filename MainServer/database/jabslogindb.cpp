#include "jabslogindb.h"

#include <QString>
#include "global/elogin.h"

#include <QFile>
#include <QTextStream>
#include <QMap>

struct SLoginUser
{
	JID m_userid;
	QString m_loginname;
	QString m_passwd;
	JRole m_role;
};

static QMap<JID,SLoginUser> s_loginusers;
static QMap<QString,JID> s_nameToId;

JAbsLoginDB::JAbsLoginDB()
{
	static bool first=true;
	if(first)
	{
		first=false;
		QFile file("../database/login");
		file.open(QIODevice::ReadOnly);
		QTextStream stream(&file);
		for(int i=0;i<1000;++i)
		{
			if(stream.atEnd()) break;
			SLoginUser user;
			stream>>user.m_userid;
			stream>>user.m_loginname;
			stream>>user.m_passwd;
			stream>>user.m_role;
			s_loginusers.insert(user.m_userid,user);
			s_nameToId.insert(user.m_loginname,user.m_userid);
		}
	}
}

JID JAbsLoginDB::checkLoginName(const QString& loginname)
{
	return s_nameToId.value(loginname,-1);
}

bool JAbsLoginDB::checkPasswd(JID userId,const QString& passwd)
{
	if(!s_loginusers.contains(userId)) return false;
	return s_loginusers.value(userId).m_passwd==passwd;
}

bool JAbsLoginDB::checkRole(JID userId,JID role)
{
	if(!s_loginusers.contains(userId)) return false;
	return s_loginusers.value(userId).m_role & (1<<role);
}
