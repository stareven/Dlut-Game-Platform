#include "jgameinfo.h"

#include <QDataStream>

using namespace NetworkData;

/*!
	\class JGameInfo jgameinfo.h <DataStruct/JGameInfo>
	\ingroup global
	\brief 游戏信息
	
	与一个游戏相关的信息。
*/

/*!
    \brief 构造函数
    
    传入 gameId
*/
JGameInfo::JGameInfo(JID gameId)
	:JSerializableData(gameId)
{
}

/*!
    \brief 构造函数
    
    传入完整信息。 \n
    \a gameId 游戏ID \n
    \a name 游戏名称 \n
    \a version 版本 \n
    \a author 作者ID \n
    \a runner 运营者ID \n
    \a introduction 文字介绍 \n
    \a serverId 游戏服务器ID \n
    \a downloadUrl 游戏客户端下载地址 \n
*/
JGameInfo::JGameInfo(JID gameId,
		  const QString& name,
		  const JVersion& version,
		  JID author,
		  JID runner,
		  const QString& introduction,
		  JID serverId,
		  const QUrl& downloadUrl)
	:JSerializableData(gameId),
	m_name(name),
	m_version(version),
	m_author(author),
	m_runner(runner),
	m_introduction(introduction),
	m_serverId(serverId),
	m_downloadUrl(downloadUrl)
{
}

/*!
    \brief 从二进制数据中序列化出各成员内容
*/
void JGameInfo::fromByteArray(const QByteArray& data)
{
	QDataStream stream(data);
	JID id;
	stream>>id;
	setId(id);
	stream>>m_name;
	stream>>m_version;
	stream>>m_author;
	stream>>m_runner;
	stream>>m_introduction;
	stream>>m_serverId;
	stream>>m_downloadUrl;
}

/*!
    \brief 将成员内容序列化为二进制数据
*/
QByteArray JGameInfo::toByteArray()const
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<getId();
	stream<<m_name;
	stream<<m_version;
	stream<<m_author;
	stream<<m_runner;
	stream<<m_introduction;
	stream<<m_serverId;
	stream<<m_downloadUrl;
	return data;
}

/*!
    \brief 获得头信息
    
    \sa JSerializableData::head()
*/
JHead JGameInfo::head()const
{
	JHead head=JHead(getId(),EIT_GameInfo,0);
	return head;
}

/*!
    \brief 返回 gameId
*/
JID JGameInfo::getGameId()const
{
	return getId();
}

/*!
    \brief 返回游戏名称
*/
const QString& JGameInfo::getName()const
{
	return m_name;
}

/*!
    \brief 返回游戏版本
*/
const JVersion& JGameInfo::getVersion()const
{
	return m_version;
}

/*!
    \brief 返回游戏作者ID
*/
JID JGameInfo::getAuthor()const
{
	return m_author;
}

/*!
    \brief 返回游戏运营者ID
*/
JID JGameInfo::getRunner()const
{
	return m_runner;
}

/*!
    \brief 返回游戏文字介绍
*/
const QString& JGameInfo::getIntroduction()const
{
	return m_introduction;
}

/*!
    \brief 返回游戏服务器ID
*/
JID JGameInfo::getServerId()const
{
	return m_serverId;
}

/*!
    \brief 返回游戏客户端下载地址
*/
const QUrl& JGameInfo::getDownloadUrl()const
{
	return m_downloadUrl;
}
