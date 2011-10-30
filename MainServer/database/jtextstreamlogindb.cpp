#include "jtextstreamlogindb.h"

#include <Global/Global>
#include <Global/Login>

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

JTextStreamLoginDB::JTextStreamLoginDB(QObject *parent)
	:JAbstractLoginDB(parent)
{
	if(s_loginusers.isEmpty())
	{
		QFile file("../database/login");
		file.open(QIODevice::ReadOnly | QIODevice::Text);
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
		}
	}
}

JID JTextStreamLoginDB::checkLoginName(const QString& loginname)
{
	foreach(SLoginUser user,s_loginusers){
		if(user.m_loginname == loginname){
			return user.m_userid;
		}
	}
	return -1;
}

bool JTextStreamLoginDB::checkPasswd(JID userId,const QString& passwd)
{
	if(!s_loginusers.contains(userId)) return false;
	return s_loginusers.value(userId).m_passwd==passwd;
}

bool JTextStreamLoginDB::checkRole(JID userId,JID role)
{
	if(!s_loginusers.contains(userId)) return false;
	return s_loginusers.value(userId).m_role & (1<<role);
}

void JTextStreamLoginDB::flush()
{
	if(s_loginusers.isEmpty()) return;
	QFile file("../database/login");
	file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
	QTextStream stream(&file);
	foreach(SLoginUser user,s_loginusers){
		stream<<user.m_userid;
		stream<<user.m_loginname;
		stream<<user.m_passwd;
		stream<<user.m_role;
		stream<<endl;
	}
	s_loginusers.clear();
}
