#include "jgameinfosocket.h"

#include <QDataStream>

#include "ssubserver.h"

JGameInfoSocket::JGameInfoSocket(QObject *parent) :
    JSocketBase(parent)
{
}

void JGameInfoSocket::sendCrypro(JID id,const QByteArray& crypro)
{
    QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<id;
    outstream<<crypro;
    sendData(outdata);
}

//void JGameInfoSocket::rqsIdList()
//{
//    QByteArray outdata;
//    QDataStream outstream(&outdata,QIODevice::WriteOnly);
//    outstream<<(JID)EGP_IDLIST;
//    sendData(outdata);
//}

void JGameInfoSocket::rqsGameList()
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)SubServer::EGP_GameList;
    sendData(outdata);
}

void JGameInfoSocket::rqsServers(JID gameId)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)SubServer::EGP_Servers;
	outstream<<gameId;
    sendData(outdata);
}

void JGameInfoSocket::dataProcess(const QByteArray& data)
{
    QDataStream stream(data);
    JID protocol;
	static bool plh=false;
	if(!plh)
	{
		stream>>plh;
		rcvPassLoginHash(plh);
		return;
	}
    stream>>protocol;
	switch((SubServer::EGameInfoProtocol)protocol)
    {
	case SubServer::EGP_GameList:
        {
			QList<SubServer::SGameInfo2> gamelist;
			stream>>gamelist;
			emit rcvGameList(gamelist);
        }
        break;
	case SubServer::EGP_Servers:
        {
			QMap<JVersion,QSet<JID> > servers;
			stream>>servers;
			emit rcvServers(servers);
        }
        break;
    }
}
