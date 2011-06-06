#include "ssubserver.h"

#include <QDataStream>

QDataStream& operator >> (QDataStream& stream,SubServer::SSubServer& ss)
{
	stream>>ss.m_serverId;
	stream>>ss.m_name;
	stream>>ss.m_address;
	stream>>ss.m_port;
	stream>>(JID&)ss.m_type;
	return stream;
}

QDataStream& operator >> (QDataStream& stream,SubServer::SGameInfo1& gi)
{
	stream>>gi.m_gameId;
	stream>>gi.m_name;
	stream>>gi.m_version;
	return stream;
}

QDataStream& operator >> (QDataStream& stream,SubServer::SSubServerInfo0& ss)
{
	stream>>(SubServer::SSubServer&)ss;
	stream>>ss.m_games;
	return stream;
}

QDataStream& operator >> (QDataStream& stream,SubServer::SGameInfo2&)
{
	return stream;
}
