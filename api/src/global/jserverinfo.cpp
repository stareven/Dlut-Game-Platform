#include "jserverinfo.h"

using namespace NetworkData;

/*!
    \class JServerInfo jserverinfo.h <DataStruct/JServerInfo>
    \ingroup global
    \brief 记录了游戏服务器相关信息
    
    成员请见构造函数
*/

/*!
    \brief 构造函数
    
    \a serverId 表示游戏服务器ID
*/
JServerInfo::JServerInfo(JID serverId)
	:JSerializableData(serverId)
{
}

/*!
    \brief 构造函数
    
    \a serverId 游戏服务器ID \n
    \a name 游戏服务器名称 \n
    \a runner 服务器运营者ID \n
    \a host 服务器地址和端口
*/
JServerInfo::JServerInfo(JID serverId,
			const QString& name,
			JID runner,
			const SHost& host)
	:JSerializableData(serverId),
	m_name(name),
	m_runner(runner),
	m_host(host)
{
}

void JServerInfo::fromByteArray(const QByteArray& data)
{
	QDataStream stream(data);
	JID id;
	stream>>id;
	setId(id);
	stream>>m_name;
	stream>>m_runner;
	stream>>m_host.m_address;
	stream>>m_host.m_port;
}

QByteArray JServerInfo::toByteArray()const
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<getId();
	stream<<m_name;
	stream<<m_runner;
	stream<<m_host.m_address;
	stream<<m_host.m_port;
	return data;
}

JHead JServerInfo::head()const
{
	JHead head=JHead(getId(),EIT_ServerInfo,0);
	return head;
}

/*!
    \brief 返回服务器ID
*/
JID JServerInfo::getServerId()const
{
	return getId();
}

/*!
    \brief 返回服务器名称
*/
const QString& JServerInfo::getName()const
{
	return m_name;
}

/*!
    \brief 返回运营者ID
*/
JID JServerInfo::getRunner()const
{
	return m_runner;
}

/*!
    \brief 返回服务器地址和端口
    
    \sa SHost
*/
const SHost& JServerInfo::getHost()const
{
	return m_host;
}
