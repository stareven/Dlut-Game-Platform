#include "jtextstreamlogindb.h"

#include <Global/Global>
#include <Global/Login>
#include <Global/Register>

#include <QFile>
#include <QTextStream>
#include <QMap>

struct SLoginUser
{
	JID m_userid;
	QString m_loginname;
	QString m_passwd;
	JRoleCombination m_role;
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
			if(stream.atEnd()) break;
			stream>>user.m_loginname;
			if(stream.atEnd()) break;
			stream>>user.m_passwd;
			if(stream.atEnd()) break;
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

QString JTextStreamLoginDB::getLoginName(JID userId)
{
	return s_loginusers.value(userId).m_loginname;
}

QString JTextStreamLoginDB::getPassword(JID userId)
{
	return s_loginusers.value(userId).m_passwd;
}

JCode JTextStreamLoginDB::addLoginUser(const QString& loginname,const QString& password)
{
	JID userId;
	for(userId=1001;userId<65535;++userId){
		if(!s_loginusers.contains(userId)){
			SLoginUser user;
			user.m_userid = userId;
			user.m_loginname = loginname;
			user.m_passwd = password;
			user.m_role = 1<<ROLE_GAMEPLAYER;
			s_loginusers.insert(user.m_userid,user);
			return 0;
		}
	}
	return ER_UserIdFull;
}

JRoleCombination JTextStreamLoginDB::getRoleCombination(JID userId)
{
	if(s_loginusers.contains(userId)){
		return s_loginusers.value(userId).m_role;
	}
	return -1;
}

void JTextStreamLoginDB::setRoleCombination(JID userId,JRoleCombination role)
{
	if(s_loginusers.contains(userId)){
		s_loginusers[userId].m_role=role;
	}
}

void JTextStreamLoginDB::flush()
{
	if(s_loginusers.isEmpty()) return;
	QFile file("../database/login");
	file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
	QTextStream stream(&file);
	foreach(SLoginUser user,s_loginusers){
		stream<<user.m_userid<<' ';
		stream<<user.m_loginname<<' ';
		stream<<user.m_passwd<<' ';
		stream<<user.m_role;
		stream<<endl;
	}
	s_loginusers.clear();
}
