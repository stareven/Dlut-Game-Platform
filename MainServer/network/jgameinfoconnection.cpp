#include "jgameinfoconnection.h"

#include <QDataStream>

#include "service/jsubserversrv.h"
#include "global/ssubserver.h"

JGameInfoConnection::JGameInfoConnection(QTcpSocket* socket,QObject *parent) :
	JPlhConnectionBase(socket,parent)
{
}

void JGameInfoConnection::afterPlh(const QByteArray& data)
{
    QDataStream stream(data);
    JID protocol;
    stream>>protocol;
	switch((SubServer::EGameInfoProtocol)protocol)
	{
	case SubServer::EGP_GameList:
        {
            QByteArray outdata;
            QDataStream outstream(&outdata,QIODevice::WriteOnly);
			SubServer::JGameInfoSrv gisp;
			outstream<<(JID)SubServer::EGP_GameList;
			outstream<<gisp.getGameList ();
            sendData(outdata);
        }
        break;
	case SubServer::EGP_Servers:
		{
            QByteArray outdata;
            QDataStream outstream(&outdata,QIODevice::WriteOnly);
			SubServer::JGameInfoSrv gisp;
			JID gameId;
			JVersion version;
			stream>>gameId;
			stream>>version;
			outstream<<(JID)SubServer::EGP_Servers;
			outstream<<gameId;
			outstream<<version;
			outstream<<gisp.getServers (gameId,version);
            sendData(outdata);
        }
		break;
	case SubServer::EGP_ServerInfo:
		{
			QByteArray outdata;
			QDataStream outstream(&outdata,QIODevice::WriteOnly);
			SubServer::JGameInfoSrv gisp;
			JID serverId;
			stream>>serverId;
			SubServer::SSubServer si;
			si=gisp.getServerInfo(serverId);
			outstream<<(JID)SubServer::EGP_ServerInfo;
			outstream<<si;
			sendData(outdata);
		}
    }
}
