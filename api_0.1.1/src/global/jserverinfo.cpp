#include "jserverinfo.h"

using namespace NetworkData;

JServerInfo::JServerInfo()
{
}

void JServerInfo::fromByteArray(const QByteArray& data)
{
	QDataStream stream(data);
	stream>>m_serverId;
	stream>>m_name;
	stream>>m_host.m_address;
	stream>>m_host.m_port;
}

QByteArray JServerInfo::toByteArray()const
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<m_serverId;
	stream<<m_name;
	stream<<m_host.m_address;
	stream<<m_host.m_port;
	return data;
}

JHead JServerInfo::head(JID id)const
{
	JHead head=JHead(id,EIT_ServerInfo,0);
	return head;
}

const QString& JServerInfo::getName()const
{
	return m_name;
}
