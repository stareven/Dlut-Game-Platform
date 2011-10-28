#ifndef SSUBSERVER_H
#define SSUBSERVER_H

#include <QString>
#include <QHostAddress>
#include <QList>

#include "jversion.h"
#include "shost.h"
#include "jglobal.h"
#include "globalapi_global.h"

/*!
	\file ssubserver.h
	\brief 定义了 SubServer 命名空间。
*/

namespace SubServer{
	struct SGameInfo0 {
		JID m_gameId;
		QString m_name;
	};
	struct SGameInfo1 : public SGameInfo0{
		JVersion m_version;
	};
	struct SGameInfo2 : public SGameInfo1{
		JID m_author;
		QString m_introduction;
	};
	struct SSubServer : public SHost{
		JID m_serverId;
		QString m_name;
		enum EType{ET_GameServer,ET_GameFileServer} m_type;
	};
	struct SGameInfo3 : public SGameInfo2{
		JID m_gameServerId;
		JID m_gameFileServerId;
	};
	struct SGameInfo4 : public SGameInfo2{
		QMap<JVersion,SSubServer> m_gameServer;
		QMap<JVersion,SSubServer> m_gameFileServer;
	};
	struct SGameServerInfo0 : public SSubServer{
		SGameInfo1 m_gameinfo;
	};
	struct SGameFileServerInfo0 : public SSubServer{
		QList<SGameInfo1> m_games;
	};
	struct SGameInfo_ID_VSN{
		JID m_gameId;
		JVersion m_version;
	};
	
	/*!
		\brief SubServer协议
	
		SubServer 向 MainServer发送相关信息的协议。
	*/
	enum ESubServerProtocol{
		ESP_ServerInfo,///< 发送服务器信息
		ESP_GameInfo,///< 发送游戏信息
		ESP_Relation,///< 发送关联信息
		ESP_Command,///< 发送命令
	};
	enum EGameInfoProtocol{
		EGP_GameList,
		EGP_Servers,
		EGP_ServerInfo,
	};
}

class QDataStream;
GLOBALAPISHARED_EXPORT QDataStream& operator >> (QDataStream&,SubServer::SSubServer&);
GLOBALAPISHARED_EXPORT QDataStream& operator << (QDataStream&,const SubServer::SSubServer&);
GLOBALAPISHARED_EXPORT QDataStream& operator >> (QDataStream&,SubServer::SGameInfo2&);
GLOBALAPISHARED_EXPORT QDataStream& operator << (QDataStream&,const SubServer::SGameInfo2&);

#endif // SSUBSERVER_H
