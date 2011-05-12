#include "jsocketbase.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QElapsedTimer>
#include <QCoreApplication>

JSocketBase::JSocketBase(QObject *parent) :
    QObject(parent)
{
    m_socket = new QTcpSocket(this);
    m_socket->setObjectName("socket");
    QMetaObject::connectSlotsByName(this);
}

void JSocketBase::connectToHost(const QHostAddress& address,
                    quint16 port)
{
    if(m_socket->state()==QAbstractSocket::ConnectedState)
    {
        if(m_socket->peerAddress()==address && m_socket->peerPort()==port)
        {
            on_socket_connected();
            return;
        }else{
            m_socket->disconnectFromHost();
        }
    }
    m_socket->connectToHost(address,port);
}

bool JSocketBase::isConnected()const
{
    //qDebug()<<m_socket->state();
    return m_socket->state()==QAbstractSocket::ConnectedState;
}

void JSocketBase::on_socket_connected()
{
    emit SocketCode(EN_CONNECTED);
}

void JSocketBase::on_socket_disconnected()
{
    emit SocketCode(EN_DISCONNECTED);
}

void JSocketBase::on_socket_readyRead()
{
    //qDebug()<<"JSocketBase::on_socket_readyRead";
    static int size=0;
    while(m_socket->bytesAvailable()>0)
    {
        if(size>0)
        {
            //qDebug()<<"size="<<size;
            QByteArray data=m_socket->read(size);
            //qDebug()<<"read data size="<<data.size();
            size=0;
            dataProcess(data);
        }else if(m_socket->bytesAvailable()>=sizeof(int)){//size==0
            QDataStream stream(m_socket);
            stream>>size;
        }
    }
}

void JSocketBase::on_socket_error ( QAbstractSocket::SocketError socketError )
{
    qDebug()<<"JSocketBase::on_socket_error : "<<socketError;
}

void JSocketBase::sendData(const QByteArray& data)
{
//    QElapsedTimer t;
//    t.start();
//    bool connected=false;
//    int elapse=1000;
//    while(t.elapsed()<elapse)
//    {
//        if(m_socket->state()==QAbstractSocket::ConnectedState)
//        {
//            connected=true;
//            break;
//        }
//        QCoreApplication::processEvents();
//    }
//    if(!connected)
//    {
//        qDebug()<<"JSocketBase::sendData : socket not connected wait for "<<elapse<<" msec .";
//        return;
//    }
    if(m_socket->state()!=QAbstractSocket::ConnectedState)
    {
        qDebug()<<"JSocketBase::sendData : socket not connected .";
    }
    int size=data.size();
    QDataStream outsocketstream(m_socket);
    outsocketstream<<size;
    m_socket->write(data);
}
