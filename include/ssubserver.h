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
		JID m_serverid;
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
		SSubServer m_gameServer;
		SSubServer m_gameFileServer;
	};

	struct SGameServerInfo0 : public SSubServer{
		SGameInfo0 m_gameinfo;
	};
	struct SGameFileServerInfo0 : public SSubServer{
		QList<SGameInfo1> m_games;
	};
	enum EProtocol{
		EP_LoginHash,
		EP_ServerInfo,
		EP_Command,
	};
}

#endif //SSUBSERVER_H
