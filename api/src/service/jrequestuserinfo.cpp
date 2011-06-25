#include "service/jrequestuserinfo.h"

#include <QCoreApplication>

#include "network/jrequestuserinfosocket.h"
#include "global/jelapsedtimer.h"


QMap<JID,UserInfo::SUserInfo> JRequestUserInfo::s_userinfolist;

JRequestUserInfo::JRequestUserInfo(QObject *parent) :
    JPlhRequestBase(parent)
{
	m_socket=new JRequestUserInfoSocket(this);
	connect(m_socket,SIGNAL(rcvUserInfo(UserInfo::SUserInfo)),SLOT(on_socket_rcvUserInfo(UserInfo::SUserInfo)));
	setSocket(m_socket);
}

UserInfo::SUserInfo JRequestUserInfo::rqsUserInfo(JID userId)
{
	if(s_userinfolist.contains(userId))
	{
		return s_userinfolist.value(userId);
	}
	m_socket->rqsUserInfo(userId);
	if(waitForUserInfo(userId,1000))
	{
		return s_userinfolist.value(userId);
	}
	return UserInfo::SUserInfo();
}

bool JRequestUserInfo::waitForUserInfo(JID userId,int msecs)const
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(s_userinfolist.contains(userId))
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return s_userinfolist.contains(userId);
}

void JRequestUserInfo::on_socket_rcvUserInfo(const UserInfo::SUserInfo& userinfo)
{
	s_userinfolist.insert(userinfo.m_userId,userinfo);
}

static JRequestUserInfo a;
