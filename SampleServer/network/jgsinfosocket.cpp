#include "jgsinfosocket.h"

#include "egameserver.h"

JGsInfoSocket::JGsInfoSocket(QObject *parent) :
    JSocketBase(parent)
{
}

void JGsInfoSocket::sendCrypro(JID id,const QByteArray& crypro)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)GameServer::EP_LoginHash;
    outstream<<id;
    outstream<<crypro;
    sendData(outdata);
}

void JGsInfoSocket::sendGsInfo(const SGameInfo& gi)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)GameServer::EP_GameServer;
    outstream<<gi;
    sendData(outdata);
}

void JGsInfoSocket::dataProcess(const QByteArray& data)
{
    QDataStream stream(data);
    JID protocol;
    stream>>protocol;
    switch((GameServer::EProtocol)protocol)
    {
    case GameServer::EP_LoginHash:
        bool plh;//pass login hash
        stream>>plh;
        emit rcvPassLoginHash(plh);
        break;
    case GameServer::EP_GameServer:
        JID gameid;
        stream>>gameid;
        emit rcvGsInfo(gameid);
        break;
    }
}
