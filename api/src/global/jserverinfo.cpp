#include "jserverinfo.h"

using namespace NetworkData;

JServerInfo::JServerInfo(JID serverId)
	:JSerializableData(serverId)
{
}

void JServerInfo::fromByteArray(const QByteArray& data)
{
	QDataStream stream(data);
	JID id;
	stream>>id;
	setId(id);
	stream>>m_name;
	stream>>m_host.m_address;
	stream>>m_host.m_port;
}

QByteArray JServerInfo::toByteArray()const
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<getId();
	stream<<m_name;
	stream<<m_host.m_address;
	stream<<m_host.m_port;
	return data;
}

JHead JServerInfo::head()const
{
	JHead head=JHead(getId(),EIT_ServerInfo,0);
	return head;
}

JID JServerInfo::getServerId()const
{
	return getId();
}

const QString& JServerInfo::getName()const
{
	return m_name;
}
