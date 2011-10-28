#include "service/jrequestuserinfo.h"

#include <QCoreApplication>

#include "network/jrequestuserinfosocket.h"
#include "global/jelapsedtimer.h"


QMap<JID,UserInfo::SUserInfo> JRequestUserInfo::s_userinfolist;

/*!
	\file jrequestuserinfo.h
	\brief 定义了 JRequestUserInfo 类
*/

/*!
	\class JRequestUserInfo jrequestuserinfo.h "service/jrequestuserinfo.h"
	\ingroup client
	\brief 获取用户信息

	JRequestUserInfo对获取用户信息请求提供一个基本的封装。\n
	请求的过程：\n
	  -# 通过 JRequestPort 获得用户信息服务的端口。\n
	  -# 调用 connectToHost() 函数连接服务器。\n
	  -# 调用 sendLoginHashCode() 函数发送Login hash code。\n
	  -# 调用 rqsUserInfo() 函数获取用户信息。\n

	\sa UserInfo::SUserInfo
*/

/*!
	\brief 构造函数。
*/
JRequestUserInfo::JRequestUserInfo(QObject *parent) :
    JLhcRequestBase(parent)
{
	m_socket=new JRequestUserInfoSocket(this);
	connect(m_socket,SIGNAL(rcvUserInfo(UserInfo::SUserInfo)),SLOT(on_socket_rcvUserInfo(UserInfo::SUserInfo)));
	setSocket(m_socket);
}

/*!
	\brief 获取\a userId 的用户信息。

	这个函数会等待一段时间直到收到请求结果。\n
	如果请求失败，它会返回 UserInfo::SUserInfo() 。\n
	这个函数会保存已经获取的用户信息，无论你是否是在同一个JRequestUserInfo 的实例中调用。\n
	如果请求一个已保存的值，这个函数会立即返回这个值。
*/
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
