#include "jportconnection.h"

#include <QDataStream>
#include <QDebug>

#include "global/eportsrv.h"
#include "service/jloginhash.h"

JPortConnection::JPortConnection(JPortService::EPortServer port,QTcpSocket* socket,QObject *parent) :
    JConnectionBase(socket,parent),
    m_srv(port)
{
    m_passLoginHash=(port==JPortService::EPS_FREE);
}

void JPortConnection::dataProcess(const QByteArray& data)
{
    QDataStream stream(data);
    JID protocol;
    stream>>protocol;
    switch((EPSProtocol)protocol)
    {
    case EPP_LOGINHASH:
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
            outstream<<(JID)EPP_LOGINHASH;
            outstream<<m_passLoginHash;
            sendData(outdata);
        }
        break;
    case EPP_PORT:
        {
            if(!m_passLoginHash)
            {
                closeConnect();
                break;
            }
            JID servertype;
            stream>>servertype;
            QByteArray outdata;
            QDataStream outstream(&outdata,QIODevice::WriteOnly);
            outstream<<(JID)EPP_PORT;
            outstream<<m_srv.getSubServerPort((EServerType)servertype);
            sendData(outdata);
        }
        break;
    default:
        qDebug()<<"JPortConnection::dataProcess error protocol"<<protocol;
        break;
    }
}
