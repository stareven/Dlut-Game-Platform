#include "jsubserverconnection.h"

#include <QDataStream>
#include <QDebug>

#include "ssubserver.h"
#include "service/jsubserversrv.h"

JSubServerConnection::JSubServerConnection(QTcpSocket* socket,QObject *parent) :
	JPlhConnectionBase(socket,parent)
{
}

void JSubServerConnection::afterPlh(const QByteArray &data)
{
	QDataStream stream(data);
	JID protocol;
	stream>>protocol;
	SubServer::JSubServerSrv sss;
	switch((SubServer::ESubServerProtocol)protocol)
	{
	case SubServer::ESP_ServerInfo:
		{
			SubServer::SSubServer subserver;
			stream>>subserver;
			JCode code=sss.addSubServer (subserver);
			QByteArray outdata;
			QDataStream outstream(&outdata,QIODevice::WriteOnly);
			outstream<<(JID)SubServer::ESP_ServerInfo;
			outstream<<code;
			sendData(outdata);
		}
		break;
	case SubServer::ESP_GameInfo:
		{
			SubServer::SGameInfo2 gameinfo;
			stream>>gameinfo;
			JCode code=sss.updateGameInfo (gameinfo);
			QByteArray outdata;
			QDataStream outstream(&outdata,QIODevice::WriteOnly);
			outstream<<(JID)SubServer::ESP_GameInfo;
			outstream<<code;
			sendData(outdata);
		}
		break;
	case SubServer::ESP_Relation:
		{
			JID serverId,gameId;
			JVersion gameVersion;
			stream>>serverId>>gameId>>gameVersion;
			JCode code=sss.addRelation (serverId,gameId,gameVersion);
			QByteArray outdata;
			QDataStream outstream(&outdata,QIODevice::WriteOnly);
			outstream<<(JID)SubServer::ESP_Relation;
			outstream<<code;
			sendData(outdata);
		}
		break;
	case SubServer::ESP_Command:
		{
			qDebug()<<"JSubServerConnection::afterPlh : undefined protocol.";
		}
		break;
	}
}
