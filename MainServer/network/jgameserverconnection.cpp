#include "jgameserverconnection.h"

#include <QDataStream>

#include "service/jloginhash.h"
#include "egameserver.h"
#include "sgame.h"
#include "service/jgameinfosrv.h"

JGameServerConnection::JGameServerConnection(QTcpSocket* socket,QObject *parent) :
    JConnectionBase(socket,parent)
{
    m_passLoginHash=false;
}

void JGameServerConnection::dataProcess(const QByteArray& data)
{
    QDataStream stream(data);
    JID protocol;
    stream>>protocol;
    switch((GameServer::EProtocol)protocol)
    {
    case GameServer::EP_LoginHash:
        {
            if(!m_passLoginHash)
            {
                JID userid;
                QByteArray crypro;
                JLoginHash::JCheck check;
                stream>>userid>>crypro;
                m_passLoginHash=(0==check.check(userid,crypro));
            }
            QByteArray outdata;
            QDataStream outstream(&outdata,QIODevice::WriteOnly);
            outstream<<(JID)GameServer::EP_LoginHash;
            outstream<<m_passLoginHash;
            sendData(outdata);
        }
        break;
    case GameServer::EP_GameServer:
        {
            if(!m_passLoginHash)
            {
                closeConnect();
                break;
            }
            SGameInfo gi;
            stream>>gi;
            JGameInfoSrv::JGis4Admin gis;
            gis.addGame(gi);
            QByteArray outdata;
            QDataStream outstream(&outdata,QIODevice::WriteOnly);
            outstream<<(JID)GameServer::EP_GameServer;
            outstream<<gi.m_gameId;
            sendData(outdata);
        }
    }
}
