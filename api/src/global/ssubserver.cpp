#include "global/ssubserver.h"

#include <QDataStream>

/*!
	\namespace SubServer
	\ingroup global
	\brief 定义了SubServer需要用到的一些数据结构。

	我们将GameServer和GameFileServer统一称为SubServer。\n
	这里定义了SubServer需要用到的一些数据结构。
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

QDataStream& operator >> (QDataStream& stream,SubServer::SGameInfo2& gi)
{
	stream>>gi.m_gameId;
	stream>>gi.m_name;
	stream>>gi.m_version;
	stream>>gi.m_author;
	stream>>gi.m_introduction;
	return stream;
}

QDataStream& operator << (QDataStream& stream,const SubServer::SGameInfo2& gi)
{
	stream<<gi.m_gameId;
	stream<<gi.m_name;
	stream<<gi.m_version;
	stream<<gi.m_author;
	stream<<gi.m_introduction;
	return stream;
}
