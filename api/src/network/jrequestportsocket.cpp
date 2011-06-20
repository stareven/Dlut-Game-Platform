#include "network/jrequestportsocket.h"

JRequestPortSocket::JRequestPortSocket(QObject *parent) :
    JSocketBase(parent)
{
}

void JRequestPortSocket::sendCrypro(JID id,const QByteArray& crypro)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)EPP_LOGINHASH;
    outstream<<id;
    outstream<<crypro;
    sendData(outdata);
}

void JRequestPortSocket::rqsServerPort(EServerType type)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)EPP_PORT;
    outstream<<type;
    sendData(outdata);
}

void JRequestPortSocket::dataProcess(const QByteArray& data)
{
    QDataStream stream(data);
    JID protocol;
    stream>>protocol;
    switch((EPSProtocol)protocol)
    {
    case EPP_LOGINHASH:
        {
            bool plh;
            stream>>plh;
            emit rcvPassLoginHash(plh);
        }
        break;
    case EPP_PORT:
        {
            quint16 port;
            stream>>port;
            emit rcvServerPort(port);
        }
        break;
    default:
        qDebug()<<"JRequestPortSocket::dataProcess error protocol"<<protocol;
        break;
    }
}
