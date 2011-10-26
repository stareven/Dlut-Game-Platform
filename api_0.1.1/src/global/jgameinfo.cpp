#include "jgameinfo.h"

#include <QDataStream>

using namespace NetworkData;

JGameInfo::JGameInfo(JID gameId)
	:JSerializableData(gameId)
{
}

void JGameInfo::fromByteArray(const QByteArray& data)
{
	QDataStream stream(data);
	JID id;
	stream>>id;
	setId(id);
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
	stream<<getId();
	stream<<m_name;
	stream<<m_version;
	stream<<m_author;
	stream<<m_introduction;
	stream<<m_serverId;
	stream<<m_downloadUrl;
	return data;
}

JHead JGameInfo::head()const
{
	JHead head=JHead(getId(),EIT_GameInfo,0);
	return head;
}

JID JGameInfo::getGameId()const
{
	return getId();
}

const QString& JGameInfo::getName()const
{
	return m_name;
}
