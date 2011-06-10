#ifndef SSUBSERVER_H
#define SSUBSERVER_H

#include <QString>
#include <QHostAddress>
#include <QList>

#include "jglobal.h"
#include "jversion.h"

namespace SubServer{
	struct SGameInfo0 {
		JID m_gameId;
		QString m_name;
	};
	struct SGameInfo1 : public SGameInfo0{
		JVersion m_version;
	};
	struct SGameInfo2 : public SGameInfo1{
		QString m_author;
		QString m_introduction;
	};
	struct SSubServer{
		JID m_serverId;
		QString m_name;
		QHostAddress m_address;//地址
		quint16 m_port;//主端口
		enum EType{ET_GameServer,ET_GameFileServer} m_type;
	};
	struct SGameInfo3 : public SGameInfo2{
		// MainServer端内部记录Game对应的Server
		JID m_gameServerId;
		JID m_gameFileServerId;
	};
	struct SGameInfo4 : public SGameInfo2{
		// 发送给Client的GameInfo
//		SSubServer m_gameServer;
//		SSubServer m_gameFileServer;
		QMap<JVersion,SSubServer> m_gameServer;
		QMap<JVersion,SSubServer> m_gameFileServer;
	};
	struct SGameServerInfo0 : public SSubServer{
		SGameInfo1 m_gameinfo;
	};
	struct SGameFileServerInfo0 : public SSubServer{
		QList<SGameInfo1> m_games;
	};
//	struct SSubServerInfo0 : public SSubServer{
//		QList<SGameInfo1> m_games;
//	};
	struct SGameInfo_ID_VSN{
		JID m_gameId;
		JVersion m_version;
	};
//	struct SSubServerInfo1 : public SSubServer{
//		QList<SGameInfo_ID_VSN> m_games;
//	};
	enum ESubServerProtocol{
		ESP_ServerInfo,
		ESP_GameInfo,
		ESP_Relation,
		ESP_Command,
	};
	enum EGameInfoProtocol{
		EGP_GameList,
		EGP_Servers,
	};
}

class QDataStream;
//QDataStream& operator >> (QDataStream&,SubServer::SSubServerInfo0&);
QDataStream& operator >> (QDataStream&,SubServer::SSubServer&);
QDataStream& operator >> (QDataStream&,SubServer::SGameInfo2&);
QDataStream& operator << (QDataStream&,const SubServer::SGameInfo2&);

#endif // SSUBSERVER_H
