#include "jgameinfo.h"

#include <QDataStream>

using namespace NetworkData;

JGameInfo::JGameInfo(JID gameId)
	:JSerializableData(gameId)
{
}
JGameInfo::JGameInfo(JID gameId,
		  const QString& name,
		  const JVersion& version,
		  JID author,
		  const QString& introduction,
		  JID serverId,
		  const QUrl& downloadUrl)
	:JSerializableData(gameId),
	m_name(name),
	m_version(version),
	m_author(author),
	m_introduction(introduction),
	m_serverId(serverId),
	m_downloadUrl(downloadUrl)
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

const JVersion& JGameInfo::getVersion()const
{
	return m_version;
}

JID JGameInfo::getAuthor()const
{
	return m_author;
}

const QString& JGameInfo::getIntroduction()const
{
	return m_introduction;
}

JID JGameInfo::getServerId()const
{
	return m_serverId;
}

const QUrl& JGameInfo::getDownloadUrl()const
{
	return m_downloadUrl;
}
