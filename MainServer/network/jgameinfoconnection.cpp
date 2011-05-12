#include "jgameinfoconnection.h"

#include <QDataStream>
//#include <QDebug>

#include "service/jloginhash.h"
#include "service/jgameinfosrv.h"
#include "egameinfo.h"

JGameInfoConnection::JGameInfoConnection(QTcpSocket* socket,QObject *parent) :
    JConnectionBase(socket,parent)
{
    m_passLoginHash=false;
}

void JGameInfoConnection::dataProcess(const QByteArray& data)
{
    QDataStream stream(data);
    JID protocol;
    stream>>protocol;
    switch((EGicProtocol)protocol)
    {
    case EGP_LOGINHASH:
        {
            if(m_passLoginHash) break;
            JID userid;
            QByteArray crypro;
            JLoginHash::JCheck check;
            stream>>userid>>crypro;
            m_passLoginHash=(0==check.check(userid,crypro));
            //qDebug()<<"JGameInfoConnection::dataProcess : EGP_LOGINHASH : "<<m_passLoginHash;
            QByteArray outdata;
            QDataStream outstream(&outdata,QIODevice::WriteOnly);
            outstream<<(JID)EGP_LOGINHASH;
            outstream<<m_passLoginHash;
            sendData(outdata);
        }
        break;
    case EGP_IDLIST:
        {
            if(!m_passLoginHash)
            {
                closeConnect();
                break;
            }
            QByteArray outdata;
            QDataStream outstream(&outdata,QIODevice::WriteOnly);
            JGameInfoSrv::JGis4Player gisp;
            outstream<<(JID)EGP_IDLIST;
            outstream<<gisp.getIdList();
            sendData(outdata);
        }
        break;
    case EGP_NAMELIST:
        {
            if(!m_passLoginHash)
            {
                closeConnect();
                break;
            }
            QByteArray outdata;
            QDataStream outstream(&outdata,QIODevice::WriteOnly);
            JGameInfoSrv::JGis4Player gisp;
            QList<SGameName> namelist=gisp.getNameList();
//            outstream<<namelist.size();
//            foreach(SGameName gn,namelist)
//            {
//                qDebug()<<"gameid="<<gn.m_gameId<<"name="<<gn.m_name;
//                outstream<<gn.m_gameId<<gn.m_name;
//            }
            outstream<<(JID)EGP_NAMELIST;
            outstream<<namelist;
//            qDebug()<<outdata.toHex().toUpper();
            sendData(outdata);
        }
        break;
    case EGP_INFOBYID:
        {
            if(!m_passLoginHash)
            {
                closeConnect();
                break;
            }
            JID userid;
            QByteArray outdata;
            QDataStream outstream(&outdata,QIODevice::WriteOnly);
            JGameInfoSrv::JGis4Player gisp;
            stream>>userid;
            outstream<<(JID)EGP_INFOBYID;
            outstream<<gisp.getInfoById(userid);
            sendData(outdata);
        }
        break;
    }
}
