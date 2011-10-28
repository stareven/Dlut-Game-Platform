#include "global/ssubserver.h"

#include <QDataStream>

/*!
	\namespace SubServer ssubserver.h "global/ssubserver.h"
	\ingroup global
	\brief 定义了SubServer需要用到的一些数据结构。

	我们将GameServer和GameFileServer统一称为SubServer。\n
	这里定义了SubServer需要用到的一些数据结构。
*/

/*!
	\brief 从流中读出 SubServer::SSubServer 的内容
	
	格式：<JID:serverId> <QString:name> <QAddress:address> <quint16:port> <JID:type> \n
	
	关于Qt QDataStream 的序列化格式，请参见Qt文档<a href="http://doc.qt.nokia.com/4.7/datastreamformat.html" target="_blank">Serializing Qt Data Types</a>
*/
QDataStream& operator >> (QDataStream& stream,SubServer::SSubServer& ss)
{
	stream>>ss.m_serverId;
	stream>>ss.m_name;
	stream>>ss.m_address;
	stream>>ss.m_port;
	JID type;
	stream>>type;
	ss.m_type=(SubServer::SSubServer::EType)type;
	return stream;
}

/*!
	\brief 将 SubServer::SSubServer 格式化为流
	
	格式参见 operator>>(QDataStream&,SubServer::SSubServer&) 。
*/
QDataStream& operator << (QDataStream& stream,const SubServer::SSubServer& ss)
{
	stream<<ss.m_serverId;
	stream<<ss.m_name;
	stream<<ss.m_address;
	stream<<ss.m_port;
	stream<<(JID)ss.m_type;
	return stream;
}

QDataStream& operator >> (QDataStream& stream,SubServer::SGameInfo1& gi)
{
	stream>>gi.m_gameId;
	stream>>gi.m_name;
	stream>>gi.m_version;
	return stream;
}

/*!
	\brief 从流中读出 SubServer::SGameInfo2 的内容
	
	格式：<JID:gameId> <QString:name> <JVersion:version> <QString:author> <QString:introduction> \n
	
	JVersion 的序列化格式参见 operator<<(QDataStream&,const JVersion&) 。\n
	关于Qt QDataStream 的序列化格式，请参见Qt文档<a href="http://doc.qt.nokia.com/4.7/datastreamformat.html" target="_blank">Serializing Qt Data Types</a>
*/
QDataStream& operator >> (QDataStream& stream,SubServer::SGameInfo2& gi)
{
	stream>>gi.m_gameId;
	stream>>gi.m_name;
	stream>>gi.m_version;
	stream>>gi.m_author;
	stream>>gi.m_introduction;
	return stream;
}

/*!
	\brief 将 SubServer::SGameInfo2 格式化为流
	
	格式参见 operator>>(QDataStream&,SubServer::SGameInfo2&) 。
*/
QDataStream& operator << (QDataStream& stream,const SubServer::SGameInfo2& gi)
{
	stream<<gi.m_gameId;
	stream<<gi.m_name;
	stream<<gi.m_version;
	stream<<gi.m_author;
	stream<<gi.m_introduction;
	return stream;
}
