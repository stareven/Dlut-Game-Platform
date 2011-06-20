#include "jrequestgameinfosocket.h"

#include <QDataStream>

#include "global/ssubserver.h"
#include "global/jversion.h"

JRequestGameInfoSocket::JRequestGameInfoSocket(QObject *parent) :
    JSocketBase(parent)
{
}

void JRequestGameInfoSocket::sendCrypro(JID id,const QByteArray& crypro)
{
    QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<id;
    outstream<<crypro;
    sendData(outdata);
}

//void JRequestGameInfoSocket::rqsIdList()
//{
//    QByteArray outdata;
//    QDataStream outstream(&outdata,QIODevice::WriteOnly);
//    outstream<<(JID)EGP_IDLIST;
//    sendData(outdata);
//}

void JRequestGameInfoSocket::rqsGameList()
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)SubServer::EGP_GameList;
    sendData(outdata);
}

void JRequestGameInfoSocket::rqsServers(JID gameId,const JVersion& version)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)SubServer::EGP_Servers;
	outstream<<gameId;
	outstream<<version;
    sendData(outdata);
}

void JRequestGameInfoSocket::dataProcess(const QByteArray& data)
{
    QDataStream stream(data);
    JID protocol;
	static bool plh=false;
	if(!plh)
	{
		stream>>plh;
		qDebug()<<plh;
		emit rcvPassLoginHash(plh);
		return;
	}
    stream>>protocol;
	switch((SubServer::EGameInfoProtocol)protocol)
    {
	case SubServer::EGP_GameList:
        {
			QList<SubServer::SGameInfo2> gamelist;
			stream>>gamelist;
			qDebug()<<"rcv game list:"<<gamelist.size ();
			emit rcvGameList(gamelist);
        }
        break;
	case SubServer::EGP_Servers:
        {
			QSet<JID> servers;
			JID gameId;
			JVersion version;
			stream>>gameId>>version>>servers;
			emit rcvServers(gameId,version,servers);
        }
        break;
    }
}
