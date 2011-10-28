#include "network/jrequestuserinfosocket.h"

#include <QDataStream>

#include "global/userinfo.h"

/*!
	\file jrequestuserinfosocket.h
	\brief 定义了 JRequestUserInfoSocket 类
*/

/*!
	\class JRequestUserInfoSocket jrequestuserinfosocket.h "network/jrequestuserinfosocket.h"
	\ingroup client
	\brief 封装请求用户信息的底层通信
	
	可以请求任何一名用户的用户信息。
	
	\note DGP API 提供了更加易于使用的 JRequestUserInfo 类来处理登录请求。
	
	\section userinfo_protocol 通信协议
	首先，这个通信协议只定义了\ref lhc_protocol "LoginHashConfirm通信协议" 中data的部分。\n
	查看完整的通信协议，请见\ref lhc_protocol "LoginHashConfirm通信协议" 。\n
	
	- 客户端向服务器端 : <JID:userId>
	  -# ::JID 类型，表示请求的用户ID。
	- 服务器端向客户端 ：<JID:userId> <UserInfo::SUserInfo:userinfo>
	  -# ::JID 类型，表示用户ID。
	  -# UserInfo::SUserInfo 类型，表示用户信息。格式化方式参见 ::operator>>(QDataStream& stream,UserInfo::SUserInfo& ui)
	
	\sa JRequestUserInfo
*/


/*!
	\fn JRequestUserInfoSocket::rcvUserInfo(const UserInfo::SUserInfo& userinfo)
	\brief 收到用户信息
	
	\a userinfo 收到的用户信息。
	
	\sa UserInfo
*/

/*!
	\brief 构造函数
	
	以后没有特殊情况，构造函数我可不可以不写了？
*/
JRequestUserInfoSocket::JRequestUserInfoSocket(QObject *parent) :
    JLhcSocketBase(parent)
{
}

/*!
	\brief 请求用户信息
	
	请求用户ID为\a userId 的用户信息。
*/
void JRequestUserInfoSocket::rqsUserInfo(JID userId)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<userId;
	sendData(outdata);
}

void JRequestUserInfoSocket::afterLhc(const QByteArray& data)
{
	QDataStream stream(data);
	JID userId;
	UserInfo::SUserInfo userinfo;
	stream>>userId;
	stream>>userinfo;
	qDebug()<<"JRequestUserInfoSocket rcv userinfo"<<userId<<userinfo.m_userId<<userinfo.m_nickname;
	emit rcvUserInfo(userinfo);
}
