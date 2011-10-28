#include "network/jrequestloginsocket.h"

#include <QTcpSocket>
#include <QHostAddress>
#include "global/elogin.h"

/*!
	\file jrequestloginsocket.h
	\brief 定义了 JRequestLoginSocket 类
*/

/*!
	\class JRequestLoginSocket jrequestloginsocket.h "network/jrequestloginsocket.h"
	\ingroup client
	\brief 封装登录请求的底层通信
	
	客户端向服务器端发送用户名和密码来请求登录。\n
	如果登录成功，服务器端会返回用户ID和\ref LoginHashCode 。\n
	
	\note DGP API 提供了更加易于使用的 JRequestLogin 类来处理登录请求。
	
	\section login_protocol 通信协议
	首先，这个通信协议只定义了\ref base_protocol "基本通信协议" 中data的部分。\n
	查看完整的通信协议，请见\ref base_protocol "基本通信协议" 。\n
	
	- 客户端向服务器端 : <QString:loginname> <QString:passwd> <JID:role>
	  -# QString 类型，以Qt QDataStream 的方式序列化为数据流，表示登录名。
	  -# QString 类型，以Qt QDataStream 的方式序列化为数据流，表示登录密码。
	  -# ::JID 类型，表示登录身份
	- 服务器端向客户端（登录成功） ： <JCode:code> <JID:userId> <QByteArray:LoginHashCode>
	  -# ::JCode 类型，0表示登录成功，其它表示不同的登录失败原因。
	  -# ::JID 类型，表示用户ID。
	  -# QByteArray 类型，以Qt QDataStream 的方式序列化为数据流，表示服务器端生成的\ref LoginHashCode 。
	- 服务器端向客户端（登录失败） ： <JCode:code>
	  -# ::JCode 类型，0表示登录成功，其它表示不同的登录失败原因。参见 ::ELogin 。
	  
	关于Qt QDataStream 的序列化格式，请参见Qt文档<a href="http://doc.qt.nokia.com/4.7/datastreamformat.html" target="_blank">Serializing Qt Data Types</a>
	
	\sa JRequestLogin
*/

/*!
	\fn JRequestLoginSocket::loginCode(const JCode& code)
	\brief 收到登录结果
	
	\a code 为0表示登录成功，其它表示不同原因的登录失败。
	
	\sa ELogin
*/

/*!
	\brief 构造函数
	
	又是构造函数。
*/
JRequestLoginSocket::JRequestLoginSocket(QObject *parent) :
	JSocketBase(parent)
{
	m_userid=-1;
    m_loginhashcode=QByteArray();
}

/*!
	\brief 发送登录请求
	
	\a loginname 表示登录名。\n
	\a passwd 表示登录密码。\n
	\a role 表示登录身份。
*/
void JRequestLoginSocket::login(const QString& loginname,const QString& passwd,const JID& role)
{
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream<<loginname<<passwd;
    stream<<role;
	sendData(data);
}

/*!
	\brief 收取服务器返回的数据
	
	这个函数会发射 loginCode() 信号。\n
	如果登录成功，会收到用户ID和\ref LoginHashCode 。\n
	之后可以调用 getUserId() 和 getLoginHashCode() 函数来获取它们。
	
	\sa getUserId(), getLoginHashCode()
*/
void JRequestLoginSocket::dataProcess(const QByteArray& data)
{
	QDataStream stream(data);
	JCode code;
	stream>>code;
	if(code==0)
	{
		stream>>m_userid>>m_loginhashcode;
	}
	emit loginCode(code);
}

/*!
	\brief 获取用户ID
	
	登录成功后，服务器会返回用户ID。\n
	如果登录失败或还未登录，这个函数会返回-1。
*/
JID JRequestLoginSocket::getUserId()const
{
    return m_userid;
}

/*!
	\brief 返回\ref LoginHashCode
	
	登录成功后，服务器会返回用户的\ref LoginHashCode 。\n
	如果登录失败或还未登录，这个函数会返回 QByteArray() 。
*/
const QByteArray& JRequestLoginSocket::getLoginHashCode()const
{
    return m_loginhashcode;
}
