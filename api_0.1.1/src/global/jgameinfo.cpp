#include "jgameinfo.h"

#include <QDataStream>

using namespace NetworkData;

JGameInfo::JGameInfo()
{
}

void JGameInfo::fromByteArray(const QByteArray& data)
{
	QDataStream stream(data);
	stream>>m_gameId;
	stream>>m_name;
	stream>>m_version;
	stream>>m_author;
	stream>>m_introduction;
	stream>>m_serverId;
	stream>>m_downloadUrl;
}

QByteArray JGameInfo::toByteArray()const
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<m_gameId;
	stream<<m_name;
	stream<<m_version;
	stream<<m_author;
	stream<<m_introduction;
	stream<<m_serverId;
	stream<<m_downloadUrl;
	return data;
}

JHead JGameInfo::head(JID id)const
{
	JHead head=JHead(id,EIT_GameInfo,0);
	return head;
}

const QString& JGameInfo::getName()
{
	return m_name;
}
