#include "jgameinfoconnection.h"

#include <QDataStream>

#include "service/jsubserversrv.h"
#include "ssubserver.h"

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
			qDebug()<<"send game list"<<gisp.getGameList ().size ();
            sendData(outdata);
        }
        break;
	case SubServer::EGP_Servers:
		{
            QByteArray outdata;
            QDataStream outstream(&outdata,QIODevice::WriteOnly);
			SubServer::JGameInfoSrv gisp;
			JID gameId;
			stream>>gameId;
			outstream<<(JID)SubServer::EGP_Servers;
			outstream<<gisp.getServersByGameid (gameId);
            sendData(outdata);
        }
		break;
    }
}
