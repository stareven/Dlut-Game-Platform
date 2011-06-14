#include "jgsinfosocket.h"

#include "ssubserver.h"

JGsInfoSocket::JGsInfoSocket(QObject *parent) :
    JSocketBase(parent)
{
}

void JGsInfoSocket::sendCrypro(JID id,const QByteArray& crypro)
{
    QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<id;
    outstream<<crypro;
    sendData(outdata);
}

//void JGsInfoSocket::sendGsInfo(const SGameInfo& gi)
//{
//    QByteArray outdata;
//    QDataStream outstream(&outdata,QIODevice::WriteOnly);
//    outstream<<(JID)GameServer::EP_GameServer;
//    outstream<<gi;
//    sendData(outdata);
//}

void JGsInfoSocket::sendServerInfo(const SubServer::SSubServer& ss)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)SubServer::ESP_ServerInfo;
	outstream<<ss;
	sendData(outdata);
}

void JGsInfoSocket::sendGameInfo(const SubServer::SGameInfo2& gi)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)SubServer::ESP_GameInfo;
	outstream<<gi;
	sendData(outdata);
}

void JGsInfoSocket::dataProcess(const QByteArray& data)
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
	switch((SubServer::ESubServerProtocol)protocol)
    {
	case SubServer::ESP_ServerInfo:
	case SubServer::ESP_GameInfo:
	case SubServer::ESP_Relation:
		{
			JCode code;
			stream>>code;
			emit rcvSendCode (protocol,code);
		}
		break;
	case SubServer::ESP_Command:
		{
			qDebug()<<"JSubServerConnection::dataProcess : undefined protocol.";
		}
		break;
//    case GameServer::EP_LoginHash:
//        bool plh;//pass login hash
//        stream>>plh;
//        emit rcvPassLoginHash(plh);
//        break;
//    case GameServer::EP_GameServer:
//        JID gameid;
//        stream>>gameid;
//        emit rcvGsInfo(gameid);
//        break;
    }
}
