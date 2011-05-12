#include "jgameinfosocket.h"

#include <QDataStream>

#include "egameinfo.h"

JGameInfoSocket::JGameInfoSocket(QObject *parent) :
    JSocketBase(parent)
{
}

void JGameInfoSocket::sendCrypro(JID id,const QByteArray& crypro)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)EGP_LOGINHASH;
    outstream<<id;
    outstream<<crypro;
    sendData(outdata);
}

void JGameInfoSocket::rqsIdList()
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)EGP_IDLIST;
    sendData(outdata);
}

void JGameInfoSocket::rqsNameList()
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)EGP_NAMELIST;
    sendData(outdata);
}

void JGameInfoSocket::rqsGameInfo(JID id)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)EGP_INFOBYID;
    outstream<<id;
    sendData(outdata);
}

void JGameInfoSocket::dataProcess(const QByteArray& data)
{
    QDataStream stream(data);
    JID protocol;
    stream>>protocol;
    switch((EGicProtocol)protocol)
    {
    case EGP_LOGINHASH:
        {
//            if(m_passLoginHash) break;
//            JID userid;
//            QByteArray crypro;
//            JLoginHash::JCheck check;
//            bool passLoginHash;
            bool plh;//pass Login Hash
            stream>>plh;
            emit rcvPassLoginHash(plh);
//            emit SocketCode(EGC_PASSLH);
//            m_passLoginHash=check.check(userid,crypro);
//            QByteArray outdata;
//            QDataStream outstream(&outdata,QIODevice::WriteOnly);
//            outstream<<(JID)EGP_LOGINHASH;
//            //outstream<<m_passLoginHash;
//            sendData(outdata);
        }
        break;
    case EGP_IDLIST:
        {
            QList<JID> idlist;
            stream>>idlist;
            emit rcvIdList(idlist);
//            emit SocketCode(EGC_RCV_IDLIST);
//            if(!m_passLoginHash)
//            {
//                closeConnect();
//                break;
//            }
//            QByteArray outdata;
//            QDataStream outstream(&outdata,QIODevice::WriteOnly);
//            JGameInfoSrv::JGis4Player gisp;
//            outstream<<(JID)EGP_IDLIST;
//            outstream<<gisp.getIdList();
//            sendData(outdata);
        }
        break;
    case EGP_NAMELIST:
        {
//            qDebug()<<data.toHex().toUpper();
            QList<SGameName> namelist;
            stream>>namelist;
//            foreach(SGameName gn,namelist)
//            {
//                qDebug()<<"gameid="<<gn.m_gameId<<" name="<<gn.m_name;
//                QByteArray gndata;
//                QDataStream gnstream(&gndata,QIODevice::WriteOnly);
//                gnstream<<gn.m_gameId;
//                qDebug()<<gndata.toHex().toUpper();
//            }
            emit rcvNameList(namelist);
//            emit SocketCode(EGC_RCV_NAMELIST);
//            if(!m_passLoginHash)
//            {
//                closeConnect();
//                break;
//            }
//            QByteArray outdata;
//            QDataStream outstream(&outdata,QIODevice::WriteOnly);
//            JGameInfoSrv::JGis4Player gisp;
//            outstream<<(JID)EGP_NAMELIST;
//            outstream<<gisp.getNameList();
//            sendData(outdata);
        }
        break;
    case EGP_INFOBYID:
        {
            SGameInfo gameinfo;
            stream>>gameinfo;
            emit rcvGameInfo(gameinfo);
//            emit SocketCode(EGC_RCV_INFO);
//            if(!m_passLoginHash)
//            {
//                closeConnect();
//                break;
//            }
//            JID userid;
//            QByteArray outdata;
//            QDataStream outstream(&outdata,QIODevice::WriteOnly);
//            JGameInfoSrv::JGis4Player gisp;
//            stream>>userid;
//            outstream<<(JID)EGP_INFOBYID;
//            outstream<<gisp.getInfoById(userid);
//            sendData(outdata);
        }
        break;
    }
}

//QDataStream& operator>>(QDataStream& stream,SGameName& gn)
//{
//    stream>>gn.m_gameId;
//    stream>>gn.m_name;
//    return stream;
//}

//QDataStream& operator>>(QDataStream& stream,SGameInfo& gi)
//{
//    stream>>(SGameName&)gi;
//    stream>>gi.m_author;
//    stream>>gi.m_serverVersion;
//    stream>>gi.m_localVersion;
//    stream>>gi.m_introduction;
//    return stream;
//}

//QDataStream& operator>>(QDataStream& stream,JVersion& ver)
//{
//    stream>>ver.m_data;
//    return stream;
//}
