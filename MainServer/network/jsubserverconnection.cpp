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
	JSubServerSrv sss;
	switch((SubServer::EProtocol)protocol)
	{
	case SubServer::EP_ServerInfo:
		{
			SubServer::SSubServerInfo0 subserver;
			stream>>subserver;
			JCode code=sss.addServer (subserver);
			QByteArray outdata;
			QDataStream outstream(&outdata,QIODevice::WriteOnly);
			outstream<<(JID)SubServer::EP_ServerInfo;
			outstream<<code;
			sendData(outdata);
		}
		break;
	case SubServer::EP_GameInfo:
		{
			SubServer::SGameInfo2 gameinfo;
			stream>>gameinfo;
			JCode code=sss.updateGameInfo (gameinfo);
			QByteArray outdate;
			QDataStream outstream(&outdate,QIODevice::WriteOnly);
			outstream<<(JID)SubServer::EP_GameInfo;
			outstream<<code;
			sendData(outdate);
		}
		break;
	case SubServer::EP_Command:
		{
			qDebug()<<"JSubServerConnection::afterPlh : undefined protocol.";
		}
		break;
	}
}
