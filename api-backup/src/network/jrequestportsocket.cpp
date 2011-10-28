#include "network/jrequestportsocket.h"

/*!
	\file jrequestportsocket.h
	\brief 定义了 JRequestPortSocket 类
*/

/*!
	\class JRequestPortSocket jrequestportsocket.h "network/jrequestportsocket.h"
	\ingroup client
	\brief 封装请求端口列表的底层通信
	
	客户端向服务器端请求各个服务的端口。
	
	\note DGP API 提供了更加易于使用的 JRequestPort 类来处理登录请求。
	
	\section port_protocol 通信协议
	首先，这个通信协议只定义了\ref base_protocol "基本通信协议" 中data的部分。\n
	查看完整的通信协议，请见\ref base_protocol "基本通信协议" 。\n
	
	\bug 这个类的文档，我再考虑考虑。因为port协议非常混乱。
	
	\sa JRequestPort
*/

/*!
	\fn JRequestPortSocket::rcvLoginHashConfirm(bool lhc)
	\brief \ref LoginHashConfirm 的结果
	
	\a lhc 表示是否通过了\ref LoginHashConfirm 。
*/

/*!
	\fn JRequestPortSocket::rcvServerPort(quint16 port)
	\brief 表示收到端口
	
	收到端口为\a port 。\n
*/

JRequestPortSocket::JRequestPortSocket(QObject *parent) :
    JSocketBase(parent)
{
}

void JRequestPortSocket::sendLoginHashCode(JID id,const QByteArray& code)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)EPP_LOGINHASH;
    outstream<<id;
    outstream<<code;
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
            emit rcvLoginHashConfirm(plh);
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
